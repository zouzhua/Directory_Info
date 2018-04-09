#include <iostream>
#include <io.h>
#include <time.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

long long Get_File_Tree2(string path,FILE *fp) {
    long hFile = 0;              //文件句柄
    struct _finddata_t fileinfo; //文件信息结构体
    string p;                    //字符串，存放路径
    long long dir_size=0;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    if(strcmp(fileinfo.name,"System Volume Information")==0||strcmp(fileinfo.name,"$RECYCLE.BIN")==0){
                        cout<<fileinfo.name<<endl;
                        continue;
                    }
                    long long size_temp=Get_File_Tree2(p.assign(path).append("\\").append(fileinfo.name), fp);
                    dir_size+= size_temp;
                    fprintf(fp,"1 %s %s %lld\n",path.c_str(),fileinfo.name,size_temp);
                }
            } else {
                dir_size+=fileinfo.size;
                fprintf(fp,"0 %s %s %ld\n",path.c_str(),fileinfo.name,fileinfo.size);
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
    return dir_size;
}

int Get_File_Tree(string path){
    FILE *fp;
    if((fp=fopen("D:\\test.txt","w+"))==NULL)
        exit(0);
    int start_time=clock();
    Get_File_Tree2(path,fp);
    int end_time=clock();
    fclose(fp);
    return end_time-start_time;
}

int main(){
    cout<<"starting..."<<endl;
    int time=Get_File_Tree("D:");
    cout << "finished ( " <<time<<"ms )";
    return 0;
}
/* 是否是文件夹(1/0) 文件夹/文件所在路径 文件夹/文件名 大小
 * */
