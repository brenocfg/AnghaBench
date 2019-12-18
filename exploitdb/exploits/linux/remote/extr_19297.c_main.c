#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct stat {int st_size; } ;
struct TYPE_2__ {int s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EADDRNOTAVAIL ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int getopt (int,char**,char*) ; 
 int getpid () ; 
 int /*<<< orphan*/  getresponse (int,int*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int inet_addr (char*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int,...) ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

main(int argc,char **argv){
    char buffer[10000],tmp[1024],*ifile,*ofile,*b,*p;
    int sck,i,c,arg,flag=-1,fd;
    struct sockaddr_in adr;
    struct hostent *hp;
    FILE *f; struct stat sbuf;

    printf("copyright LAST STAGE OF DELIRIUM oct 1998 poland  //lsd-pl.net/\n");
    printf("sdrd for aix 4.1 4.2 PowerPC/POWER\n\n");

    if(argc!=5){
        printf("usage: %s address -g|-p|-r ifile ofile\n",argv[0]);
        exit(-1);
    }

    while((c=getopt(argc-1,&argv[1],"gpr"))!=-1){
        switch(c){
        case 'g': flag=1; break;
        case 'p': flag=2; break;
        case 'r': flag=3; break;
        default : exit(-1);
        }
    }
    if(flag==-1) exit(-1);

    ifile=argv[optind+1];
    ofile=argv[optind+2];

    sck=socket(AF_INET,SOCK_STREAM,0);
    adr.sin_family=AF_INET;
    adr.sin_port=htons(5712);
    if((adr.sin_addr.s_addr=inet_addr(argv[1]))==-1){
        if((hp=gethostbyname(argv[1]))==NULL){
            errno=EADDRNOTAVAIL;perror("error");exit(-1);
        }
        memcpy(&adr.sin_addr.s_addr,hp->h_addr,4);
    }

    if(connect(sck,(struct sockaddr*)&adr,sizeof(struct sockaddr_in))<0){
        perror("error");exit(-1);
    }

    switch(flag){
    case 1:
        printf("getting %s from %s\n",ifile,argv[1]);
        sprintf(tmp,"SDRFiles/../../../../../../../../../../../../..%s",ifile);
        sprintf(buffer,"3 %d %s",strlen(tmp),tmp);
        write(sck,buffer,strlen(buffer));
        if(getresponse(sck,&arg)){
            printf("error: no file %s:%s\n",argv[1],ifile);exit(-1);
        }
        if((fd=open(ofile,O_RDWR|O_CREAT,0600))<0){
            printf("error: create %s\n",ofile);exit(-1);
        }
        while(arg){
            if((i=read(sck,buffer,arg))<0) {perror("error");exit(-1);}   
            write(fd,buffer,i);
            arg-=i;
        } 
        break;
    case 2:
        printf("putting %s to %s:%s\n",ifile,argv[1],ofile);
        goto common;
    case 3:
        printf("replace %s:%s with %s\n",argv[1],ofile,ifile);
        goto common;

common:
        gethostname(tmp,sizeof(tmp));
        sprintf(buffer,"8 18 0 %s:%d:1",tmp,getpid());
        write(sck,buffer,strlen(buffer));
        if(getresponse(sck,&arg)){ 
            printf("error: auth\n");exit(-1);
        }
        if((fd=open(ifile,O_RDONLY))<0){
            printf("error: open %s\n",ifile);exit(-1);
        }
        fstat(fd,&sbuf);
        sprintf(tmp,"SDRFiles/../../../../../../../../../..%s",ofile);
        if(!(b=(char*)malloc(strlen(tmp)+sbuf.st_size+32))){
            printf("error: memory alloc");exit(-1);
        }
        if(flag==3) sprintf(b,"2 %d %s ",strlen(tmp)+sbuf.st_size,tmp);
        else sprintf(b,"19 %d %s ",strlen(tmp)+sbuf.st_size,tmp);
        p=b+strlen(b);
        arg=sbuf.st_size;
        while(arg){
            if((i=read(fd,p,arg))<0) {perror("error");exit(-1);}
            arg-=i;p+=i;
        }
        close(fd);
        *p=0;
        write(sck,b,strlen(b));
        if(flag==3) while(arg){
            if((i=read(sck,buffer,arg))<0) {perror("error");exit(-1);}
            arg-=i;
        }
        if(getresponse(sck,&arg)){ 
            printf("error: create %s:%s\n",argv[1],ofile);exit(-1);
        }
    }
    printf("ok!\n");
    close(fd);
}