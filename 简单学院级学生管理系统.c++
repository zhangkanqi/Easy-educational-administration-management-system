
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdio.h>
using namespace std;
#define maxn 500

ifstream fr;
ofstream fw;
int choose;//选择功能
char press;//选择是否进行操作Y/N
string FileAddress;//数据写入的文件地址
int id;//登陆时的选择
int Cournum = 7;//课程数目
int n = 0;//学生人数
char ID;//登录的身份 ：s学生（student）；t教师（teacher）；a管理员（administrator）
typedef struct student {
    string name;//姓名
    int num;//学号
    string classs;//班级
    int level;//年级
    int grades[20];//记录门课的成绩，都是整数，grades[0]不记录东西
}Student;
Student stu[maxn];
string Course[9] = { "","C++程序设计","数据结构","大学英语","线性代数","高等数学","计算机组织与结构","体育" };
float Average[8] = { 0 };//统计平均分
float PassRatee[8] = { 0 };//统计及格率

void GradeStatistics(Student stu[maxn]);//成绩统计
void AverageGrade(Student stu[maxn]);//平均分
void PassRate(Student stu[maxn]);//及格率
void CourseManage(Student stu[maxn]);//课程管理

void StudentInfo(Student stu[maxn]);//学生资料管理
void AddStudent(Student stu[maxn]);//添加学生（及其信息）
void DeleteStudent(Student stu[maxn]);//删除学生（及其信息）

void CourseManage(Student stu[maxn]);//课程管理
void AddCourse(Student stu[maxn]);//添加课程（及分数信息）
void DeleteCourse(Student stu[maxn]);//删除课程（及分数信息）
void StuAddCourse(Student stu[maxn]);//输入某个学生某门课的分数
void OutCouGrade(Student stu[maxn]);//列表输出所有学生的某门课程成绩


void StudentInquire(Student stu[maxn]);//学生查询
void OutStuInfo(int StuOrder);//输出学生信息(保存为磁盘文件）
void StuInfoSearch(Student stu[maxn]);//查询学生信息
void NumSearch(Student stu[maxn]);//按学号查询学生信息
void NameSearch(Student stu[maxn]);//按姓名查询学生信息

void StudentSort(Student stu[maxn],int s,int t);//学生依据学号排序,快速排序,升序
int partition(Student stu[maxn],int s,int t);//一趟划分
int BinSearch(Student stu[maxn],int FindNum);//e二分查找学号为FindNum的学生

void WelcomePage();//输出首页的欢迎界面
void Exit();//退出
void Read();//从文件中读取数据
void Save(int NumStu);//存储数据
void Update(Student stu[maxn]);//更新学生数据


void AverageGrade(Student stu[maxn])//平均分
{
    if(ID!='t')
    {
        cout<<"对不起，您不是教师，没有权利执行此项操作！"<<endl;
        return ;
    }
    int i, j;
    for (i = 1; i <= Cournum; i++)
    {
        int NumStu = 0;//修读该课程的学生总数
        int AllGrades = 0;//总分
        for (j = 0; j<n; j++)
        {
            if (stu[j].grades[i] != -1)//修读了这门课
            {
                NumStu++;
                AllGrades += stu[j].grades[i];
            }
        }
        Average[i] = AllGrades * 1.0 / NumStu;
    }
    cout << "课程:\t";
    for (i = 1; i <= Cournum; i++)
    {
        cout << "  " << Course[i];
    }
    cout << endl;
    cout << "平均分:\t";
    for (i = 1; i <= Cournum; i++)
    {
        printf("    %d    ", (int)Average[i]);
    }
    cout << endl;
}
void PassRate(Student stu[maxn])//及格率
{
    if(ID!='t')
    {
        cout<<"对不起，您不是教师，没有权利执行此项操作！"<<endl;
        return ;
    }
    int i, j;
    for (i = 1; i <= Cournum; i++)
    {
        int NumStu = 0, NumPass = 0;//修读该课程的学生总数和及格的学生总数
        for (j = 0; j<n; j++)
        {
            if (stu[j].grades[i] != -1)//修读了这门课
            {
                NumStu++;
                if (stu[j].grades[i] >= 60)
                    NumPass++;
            }
        }
        PassRatee[i] = NumPass * 1.0 / NumStu;
    }
    cout << "课程:\t";
    for (i = 1; i <= Cournum; i++)
    {
        cout << "    " << Course[i];
    }
    cout << endl;
    cout << "及格率:\t";
    for (i = 1; i <= Cournum; i++)
    {
        printf("\t%7.2f%%", (PassRatee[i] * 100));
    }
    cout << endl;
}
void GradeStatistics()//成绩统计
{
    while(choose!=0) {
        cout << "\t\t\t       ***********************" << endl;
        cout << "\t\t\t     *****学生成绩统计管理主菜单****" << endl;
        cout << "\t\t\t   *******************************" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t*         学生成绩统计管理            *" << endl;
        cout << "\t\t\t*                                   *" << endl;
        cout << "\t\t\t*          1.统计平均分               *" << endl;
        cout << "\t\t\t*          2.统计及格率               *" << endl;
        cout << "\t\t\t*          0.退出                    *" << endl;
        cout << "\t\t\t*                                   *" << endl;
        cout << "\t\t\t*            按Enter继续             *" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t        请输入0～2之间的任一数字" << endl;
        cout << "请选择功能对应的数字：";
        int e;
        cin>>e;
        switch (e) {
            case 1:
                AverageGrade(stu);
                break;//平均分
            case 2:
                PassRate(stu);
                break;//及格率
            case 0:
                Exit();
                return;//退出
            default:
                cout << "\t\t\t      输入错误，返回" << endl;
                break;
        }
    }

}

void OutStuInfo(int StuOrder)//输出学生信息(保存为磁盘文件）
{
    int i = StuOrder;
    cout << "请输入想要将学生信息保存到的文件的地址：";
    cin >> FileAddress;
    fw.open(FileAddress.c_str(), ofstream::out|ios::app);
    if (!fw)
    {
        cout << "文件打开出错！" << endl;
        return ;
    }
    cout << "已成功打开文件!" << endl;
    fw << "姓名：" << stu[i].name << endl;
    fw << "学号：" << stu[i].num << endl;
    fw << "班级：" << stu[i].classs << endl;
    fw << "年级：" << stu[i].level << endl;
    for (int j = 1; j <= Cournum; j++)
    {
        if(stu[i].grades[j]!=-1)
            fw << Course[j] << "：" << stu[i].grades[j] << "分" << endl;
        else
            fw << Course[j] << "：" <<"未修读" << endl;

    }
    int m=30;
    while(m--)
        fw<<"*";
    fw<<endl;
    fw.close();
    cout << "学生信息已保存到该文件中" << endl;
}
void NumSearch(Student stu[maxn])//按学号查询学生信息
{
    do {
        int FindNum,i;
        cout << "请输入想要查询的学生的学号:";
        cin >> FindNum;
        i=BinSearch(stu,FindNum)-1;
        if(i!=-1)//二分查找
        {
            cout << "学号为<" << stu[i].num << ">的学生资料已找到!" << endl;
            OutStuInfo(i);//输出学生信息(保存为磁盘文件）
        }
        else
            cout << "未找到学号为<" << FindNum << ">的学生，请输入正确的学生学号:";
        cout << "是否继续按照学号查询（Y/N)?" << endl;
        cin >> press;
    } while (press == 'Y');
}
void NameSearch(Student stu[maxn])//按姓名查询学生信息
{
    do {
        int i;
        string FindName;
        cout << "请输入想要查询的学生的姓名:";
        cin >> FindName;
        for (i = 0; i<n; i++)
            if (stu[i].name == FindName)
            {
                cout << "姓名为<" << stu[i].name << ">的学生资料已找到!" << endl;
                OutStuInfo(i);//输出学生信息(保存为磁盘文件）
                break;
            }
        if (i >= n)
            cout << "未找到姓名为<" << FindName << ">的学生，请输入正确的学生姓名:";
        cout << "是否继续按照姓名查询（Y/N)?" << endl;
        cin >> press;
    } while (press == 'Y');
}
void StuInfoSearch()//查询学生信息（保存为磁盘文件）
{
    if(ID!='s')
    {
        cout<<"对不起，您不是学生，没有权利执行此项操作！"<<endl;
        return ;
    }
    while(choose!=0) {
        cout << "\t\t\t       ***********************" << endl;
        cout << "\t\t\t     *******学生查询方式选择菜单****" << endl;
        cout << "\t\t\t   *******************************" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t*            查询方式                *" << endl;
        cout << "\t\t\t*                                   *" << endl;
        cout << "\t\t\t*          1.按学号查询              *" << endl;
        cout << "\t\t\t*          2.按姓名查询              *" << endl;
        cout << "\t\t\t*          0.退出                   *" << endl;
        cout << "\t\t\t*                                   *" << endl;
        cout << "\t\t\t*            按Enter继续             *" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t        请输入0～2之间的任一数字" << endl;
        cout << "请选择功能对应的数字：";
        int d;
        cin>>d;
        switch (d) {
            case 1:
                NumSearch(stu);
                break;//按学号查询学生信息
            case 2:
                NameSearch(stu);
                break;//按姓名查询学生信息
            case 0:
                Exit();
                return ;//退出
            default:
                cout << "\t\t\t      输入错误，返回" << endl;
                break;
        }
    }
}
void StudentInquire()//学生查询
{
    while(choose!=0) {
        cout << "\t\t\t      *************************" << endl;
        cout << "\t\t\t    *********学生查询管理主菜单*****" << endl;
        cout << "\t\t\t  *********************************" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t*            学生查询管理             *" << endl;
        cout << "\t\t\t*                                   *" << endl;
        cout << "\t\t\t*          1.查询学生信息             *" << endl;
        cout << "\t\t\t*          0.退出                    *" << endl;
        cout << "\t\t\t*                                   *" << endl;
        cout << "\t\t\t*            按Enter继续             *" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t        请输入0～1之间的任一数字" << endl;
        cout << "请选择功能对应的数字：";
        int c;
        cin>>c;
        switch (c) {
            case 1:
                StuInfoSearch();
                break;//输出学生信息
            case 0:Exit();return ;//退出
            default:
                cout << "\t\t\t      输入错误，返回" << endl;
                break;
        }
    }
}

void AddStudent(Student stu[maxn])//添加学生（及其信息）
{
    if(ID!='a')
    {
        cout<<"对不起，您不是管理员，没有权利执行此项操作！"<<endl;
        return ;
    }
    int NumStu, NumCourse;
    int i, j, k, mark, grades;//mark为课程代号,grades为分数
    cout << "请输入你想要添加学生的个数：";
    cin >> NumStu;
    k = n;
    int num = 0;
    for (i = k; i<k + NumStu; i++)
    {
        for (j = 1; j <= Cournum; j++)
            stu[i].grades[j] = -1;//把该学生的每门课的成绩初始为-1，即表示未修读
        printf("请输入你想添加的第%d个学生的资料\n", ++num);
        cout << "学号："; cin >> stu[i].num;
        if(stu[i].num>9999999||stu[i].num<1000000) {
            cout << "请输入7位学号：";
            cin>>stu[i].num;
        }
        cout << "姓名："; cin >> stu[i].name;
        cout << "班级："; cin >> stu[i].classs;
        cout << "年级："; cin >> stu[i].level;
        cout << "请输入该学生所修课程的门数和及相应的分数" << endl;
        cout << "所修课程门数："; cin >> NumCourse;
        for (j = 1; j <= NumCourse; j++)
        {
            cout << "课程代号："; cin >> mark;
            cout << "课程分数："; cin >> grades;
            stu[i].grades[mark] = grades;
        }
        n++;//学生人数+1
    }
    cout << "信息输入成功，是否保存资料到文件?(Y/N)" << endl;
    cin >> press;
    if (press == 'Y')
    {
        Save(NumStu);
    }
    else cout << "资料未保存到文件内!" << endl;
    Update(stu);
}

void DeleteStudent(Student stu[maxn])//删除学生（及其信息）管理员权限
{
    if(ID!='a')
    {
        cout<<"对不起，您不是管理员，没有权利执行此项操作！"<<endl;
        return ;
    }
    int i, j, k;
    string DeleteName;
    do {
        i = 0;
        cout << "请输入你要删除的学生名字：";
        cin >> DeleteName;
        getchar();
        while (stu[i].name != DeleteName && i<n)
            i++;
        if (i >= n)
            cout << "未查询到该学生，请输入正确的学生名字!";
        else {
            for (j = i; j<n - 1; j++)//删除一个学生，后面学生的信息往前移
            {
                stu[j].name = stu[j + 1].name;
                stu[j].num = stu[j + 1].num;
                stu[j].classs = stu[j + 1].classs;
                stu[j].level = stu[j + 1].level;
                for (k = 1; k <= Cournum; k++)
                    stu[j].grades[k] = stu[j + 1].grades[k];
            }
            n--;
            cout << "该学生信息已找到，相关资料已删除!" << endl;
        }
        cout << "是否继续删除操作（Y/N)?" << endl;
        cin >> press;
    } while (press == 'Y');
    Update(stu);
}
void StudentInfo()//学生资料管理
{
    while(choose!=0) {
        cout << "\t\t\t     **************************" << endl;
        cout << "\t\t\t   ********学生资料管理主菜单*******" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t*            学生资料管理             *" << endl;
        cout << "\t\t\t*                                   *" << endl;
        cout << "\t\t\t*          1.添加学生资料             *" << endl;
        cout << "\t\t\t*          2.删除学生资料             *" << endl;
        cout << "\t\t\t*          0.退出                    *" << endl;
        cout << "\t\t\t*                                   *" << endl;
        cout << "\t\t\t*            按Enter继续             *" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t*************************************" << endl;
        cout << "\t\t\t        请输入0～2之间的任一数字" << endl;
        cout << "请选择功能对应的数字：";
        int a;
        cin >> a;
        switch (a) {
            case 1:
                AddStudent(stu);
                break;//添加学生（及其信息）
            case 2:
                DeleteStudent(stu);
                break;//删除学生（及其信息)
            case 0:Exit();return ;//退出
            default:
                cout << "\t\t\t      输入错误，返回" << endl;
                break;
        }
    }
}

void Read()//从文件中读取数据
{
    fr.open("/Users/zhangkanqi/Desktop/studentdata.txt");
    while(fr.peek()!=EOF)
    {
        fr >> stu[n].name >> stu[n].num >> stu[n].classs >> stu[n].level;
        for (int j = 1; j <= Cournum; j++)
            fr >> stu[n].grades[j];//读取Cournum门课程的成绩
        n++;    //统计文件中学生人数
    }
    n--;
    cout << "已成功读取"<<n <<"个学生的数据！"<< endl;
    fr.close();
}
void Save(int NumStu)
{
    fw.open("/Users/zhangkanqi/Desktop/studentdata.txt", ofstream::out|ios::app);
    for (int i = n ; i<n+NumStu; i++)
    {
        fw << setw(8)<<stu[i].name << " " << stu[i].num << " " <<setw(8)<< stu[i].classs << " " <<setw(2)<< stu[i].level;
        for (int j = 1; j <= Cournum; j++)
        {
            if(stu[i].grades[j]==-1)
                fw << " " << stu[i].grades[j];
            else
                fw << " " << setw(2)<<stu[i].grades[j];//保持对齐

        }
        fw << endl;
    }
    fw.close();
    cout << "新添加的学生资料已经存储到文件中，请前往查看！" << endl;
}
void Exit()
{
    cout << "退出" << endl;
}
void CourseManage()//课程管理主菜单
{
    while (choose != 0) {
        cout << "\t\t       ************************************" << endl;
        cout << "\t\t     *************课程管理主菜单***************" << endl;
        cout << "\t\t   ********************************************" << endl;
        cout << "\t\t**************************************************" << endl;
        cout << "\t\t*                  课程管理                        *" << endl;
        cout << "\t\t*                                                *" << endl;
        cout << "\t\t*              1.输入学生课程成绩                   *" << endl;
        cout << "\t\t*              2.列表输出课程成绩                   *" << endl;
        cout << "\t\t*              3.删除课程                         *" << endl;
        cout << "\t\t*              4.添加课程                         *" << endl;
        cout << "\t\t*              0.退出系统                         *" << endl;
        cout << "\t\t*                                                *" << endl;
        cout << "\t\t*                按Enter继续                      *" << endl;
        cout << "\t\t*                                                *" << endl;
        cout << "\t\t**************************************************" << endl;
        cout << "\t\t**************************************************" << endl;
        cout << "                  请输入0～4之间的任一数字                " << endl;
        cout << "请选择功能对应的数字：";
        int b;
        cin >> b;
        switch (b) {
            case 1:
                StuAddCourse(stu);
                break;
            case 2:
                OutCouGrade(stu);
                break;
            case 3:
                DeleteCourse(stu);
                break;
            case 4:
                AddCourse(stu); break;
            case 0:Exit();return ;
            default:
                cout << "\t\t\t      输入错误，返回" << endl;
                break;
        }
    }
}
void StuAddCourse(Student stu[maxn])//输入某个学生的某门课程成绩
{
    if(ID!='t')
    {
        cout<<"对不起，您不是教师，没有权利执行此项操作！"<<endl;
        return ;
    }
    int num, coursenum, coursegrade;
    do {
        cout << "请输入你要添加课程的同学的学号：";
        cin >> num;
        if (num > 9999999 || num < 1000000) {
            cout << "请输入Cournum位学号：";
            cin >> num;
        }
        int i = BinSearch(stu, num) - 1;
        if (i != -1) //找到了学号为num的学生
        {
            cout << "请输入你要添加的课程成绩的课程代号：";
            cin >> coursenum;
            if (stu[i].grades[coursenum] == -1) {
                cout << "请输入课程成绩：";
                cin >> coursegrade;
                stu[i].grades[coursenum] = coursegrade;
                cout << "添加完毕！";
            }
            else cout << "该课程成绩已存在，无需添加"<<endl;
         }
         else cout << "不存在该学生！";
        cout << "是否继续此项操作（Y/N)?" << endl;
        cin >> press;
    }while(press=='Y');
    Update(stu);
}
void AddCourse(Student stu[])
{
    if(ID!='a')
    {
        cout<<"对不起，您不是管理员，没有权利执行此项操作！"<<endl;
        return ;
    }
    string coursename,stuname;
    int stugrade;
    cout << "请输入你想添加的课程名字：";
    cin >> coursename;
    Cournum++;
    Course[Cournum] = coursename;
    cout << "请输入该课程下所有学生的成绩"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<"请输入<"<<stu[i].name<<">该课程的成绩(-1表示未修读）：";
        cin >> stugrade;
        stu[i].grades[Cournum] = stugrade;
    }
    cout<<"已成功添加该课程及其相关的成绩信息！"<<endl;
    Update(stu);

}
void DeleteCourse(Student stu[maxn])
{
    if(ID!='a')
    {
        cout<<"对不起，您不是管理员，没有权利执行此项操作！"<<endl;
        return ;
    }
    int delecournum;
    cout << "请输入要删除的课程代号：";
    cin >> delecournum;
    for(int i=0;i<n;i++)
        stu[i].grades[delecournum]=-1;
    for(int i = Cournum; i > delecournum; i--)
        Course[i - 1] = Course[i];
    Cournum--;
    cout<<"已成功删除该课程及其相关的成绩信息！"<<endl;
    Update(stu);
}
void OutCouGrade(Student stu[maxn])
{
    if(ID!='t')
    {
        cout<<"对不起，您不是教师，没有权利执行此项操作！"<<endl;
        return ;
    }
    string CourseName;
    int d;
    cout<<"请输入你想要输出的课程成绩对应的代号：";
    cin>>d;
    cout << "请输入想要将学生信息保存到的文件的地址：";
    cin >> FileAddress;
    fw.open(FileAddress.c_str(), ofstream::out|ios::app);
    if (!fw)
    {
        cout << "文件打开出错！" << endl;
        return ;
    }
    cout << "已成功打开文件!" << endl;
    fw<<"名字    "<<Course[d]<<endl;
    for(int i=0;i<n;i++)
    {
        fw<<stu[i].name<<"  ";
        if(stu[i].grades[d]!=-1)
         fw<<stu[i].grades[d]<<endl;
        else fw<<"未修读"<<endl;
    }
    int m=30;
    while(m--)
        fw<<"*";
    fw<<endl;
    fw.close();
    cout<<"课程成绩已成功保存到该文件中，请前往查看！"<<endl;
}

void Update(Student stu[maxn])//更新学生数据
{
    fw.open("/Users/zhangkanqi/Desktop/studentdata.txt",ofstream::out);
    for (int i = 0; i<n; i++)
    {
        fw << setw(8)<<stu[i].name << " " << stu[i].num << " " <<setw(8)<< stu[i].classs << " " <<setw(2)<< stu[i].level;
        for (int j = 1; j <= Cournum; j++)
        {
            if(stu[i].grades[j]==-1)
                fw << " " << stu[i].grades[j];
            else
                fw << " " << setw(2)<<stu[i].grades[j];//保持对齐

        }
        fw << endl;
    }
    fw.close();
    cout << "新的学生信息表已更新，请前往文件查看！" << endl;
}
void WelcomePage()//输出首页的欢迎界面
{
    int id=-1;
    while(id>3||id<1)
    {
      cout << "\t\t       **********************************" << endl;
      cout << "\t\t     *************  欢迎使用  ***************" << endl;
      cout << "\t\t   *********** 计算机学院教务管理系统 ************" << endl;
      cout << "\t\t**************************************************" << endl;
      cout << "\t\t*                  登陆身份                       *" << endl;
      cout << "\t\t*                                                *" << endl;
      cout << "\t\t*                1.我是学生                       *" << endl;
      cout << "\t\t*                2.我是教师                       *" << endl;
      cout << "\t\t*                3.我是管理员                     *" << endl;
      cout << "\t\t*                                                *" << endl;
      cout << "\t\t*                按Enter继续                      *" << endl;
      cout << "\t\t*                                                *" << endl;
      cout << "\t\t**************************************************" << endl;
      cout << "\t\t**************************************************" << endl;
      cout << "                  请输入1～3之间的任一数字                " << endl;
      cout<<"请选择您的身份：";
      cin>>id;
      switch (id)
      {
          case 1:ID='s';
            break;
          case 2:ID='t';
            break;
          case 3:ID='a';
            break;
          default: cout<<"请输入1～3之间的数字！"<<endl;
            break;
      }
    }
}
int partition(Student stu[maxn],int s,int t)//一趟划分
{
    int i=s,j=t;
    Student temp=stu[i];
    while(i<j)
    {
        while(i<j && stu[j].num>=temp.num)
            j--;
        stu[i]=stu[j];
        while(i<j && stu[i].num<=temp.num )
            i++;
        stu[j]=stu[i];
    }
    stu[i]=temp;
    return i;
}
void StudentSort(Student stu[maxn],int s,int t)//学生依据学号排序,快速排序,升序
{
    int i;
    if(s<t)
    {
        i=partition(stu,s,t);
        StudentSort(stu,s,i-1);//左区间
        StudentSort(stu,i+1,t);//右区间
    }
}
int BinSearch(Student stu[maxn],int FindNum)//二分查找学号为FindNum的学生
{
    int low=0,high=n-1,mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(stu[mid].num==FindNum)
            return mid+1;
        if(stu[mid].num>FindNum)
            high=mid-1;
        else
            low=mid+1;
    }
    return 0;
}
int main()
{
    Read();
    StudentSort(stu,0,n-1);//学生依据学号排序,快速排序,升序
    WelcomePage();
    choose=-1;
    while(choose!=0) {
        cout << "\t\t       ************************************" << endl;
        cout << "\t\t     *************选择功能主菜单***************" << endl;
        cout << "\t\t   ********************************************" << endl;
        cout << "\t\t**************************************************" << endl;
        cout << "\t\t*                  操作菜单                       *" << endl;
        cout << "\t\t*                                                *" << endl;
        cout << "\t\t*              1.学生资料管理                      *" << endl;
        cout << "\t\t*              2.学生成绩统计管理                   *" << endl;
        cout << "\t\t*              3.学生课程管理                      *" << endl;
        cout << "\t\t*              4.学生查询管理                      *" << endl;
        cout << "\t\t*              0.退出系统                         *" << endl;
        cout << "\t\t*                                                *" << endl;
        cout << "\t\t*                按Enter继续                      *" << endl;
        cout << "\t\t*                                                *" << endl;
        cout << "\t\t**************************************************" << endl;
        cout << "\t\t**************************************************" << endl;
        cout << "                  请输入0～4之间的任一数字                " << endl;
        cout<<"请选择功能对应的数字：";
        cin >> choose;
        switch (choose) {
            case 1:
                StudentInfo();
                break;//学生资料管理
            case 2:
                GradeStatistics();
                break;//成绩统计
            case 3:
                CourseManage();//课程管理
                break;
            case 4:
                StudentInquire();
                break;//学生查询
            case 0:
                Exit();
                break;//退出
            default:
                cout << "\t\t\t           输入错误，返回" << endl;
                break;
        }
    }
    return 0;
}
