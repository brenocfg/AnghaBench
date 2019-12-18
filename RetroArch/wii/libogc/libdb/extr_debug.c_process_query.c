#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gdbstub_threadinfo {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int QM_MAXTHREADS ; 
 int gdbstub_getnextthread (int) ; 
 int gdbstub_getthreadinfo (int,struct gdbstub_threadinfo*) ; 
 int /*<<< orphan*/  packqmheader (char*,int,int,int) ; 
 char* packqmthread (char*,int) ; 
 int /*<<< orphan*/  packqq (char*,int,int,struct gdbstub_threadinfo*) ; 
 int parseql (char const*,int*,int*,int*) ; 
 int parseqp (char const*,int*,int*) ; 
 char* reserve_qmheader (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* thread2vhstr (char*,int) ; 

__attribute__((used)) static void process_query(const char *inp,char *outp,s32 thread)
{
	char *optr;

	switch(inp[1]) {
		case 'C':
			optr = outp;
			*optr++ = 'Q';
			*optr++ = 'C';
			optr = thread2vhstr(optr,thread);
			*optr++ = 0;
			break;
		case 'P':
			{
				s32 ret,rthread,mask;
				struct gdbstub_threadinfo info;

				ret = parseqp(inp,&mask,&rthread);
				if(!ret || mask&~0x1f) {
					strcpy(outp,"E01");
					break;
				}

				ret = gdbstub_getthreadinfo(rthread,&info);
				if(!ret) {
					strcpy(outp,"E02");
					break;
				}
				packqq(outp,mask,rthread,&info);
			}
			break;
		case 'L':
			{
				s32 ret,athread,first,max_cnt,i,done,rthread;

				ret = parseql(inp,&first,&max_cnt,&athread);
				if(!ret) {
					strcpy(outp,"E02");
					break;
				}
				if(max_cnt==0) {
					strcpy(outp,"E02");
					break;
				}
				if(max_cnt>QM_MAXTHREADS) max_cnt = QM_MAXTHREADS;

				optr = reserve_qmheader(outp);
				if(first) rthread = 0;
				else rthread = athread;

				done = 0;
				for(i=0;i<max_cnt;i++) {
					rthread = gdbstub_getnextthread(rthread);
					if(rthread<=0) {
						done = 1;
						break;
					}
					optr = packqmthread(optr,rthread);
				}
				*optr = 0;
				packqmheader(outp,i,done,athread);
			}
			break;
		default:
			break;
	}
}