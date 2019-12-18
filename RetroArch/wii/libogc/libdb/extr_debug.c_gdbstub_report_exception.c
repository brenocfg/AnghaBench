#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_3__ {int /*<<< orphan*/  SRR0; int /*<<< orphan*/ * GPR; int /*<<< orphan*/  EXCPT_Number; } ;
typedef  TYPE_1__ frame_context ;

/* Variables and functions */
 int /*<<< orphan*/  PC_REGNUM ; 
 int /*<<< orphan*/  SP_REGNUM ; 
 int /*<<< orphan*/  computeSignal (int /*<<< orphan*/ ) ; 
 void* highhex (int /*<<< orphan*/ ) ; 
 void* lowhex (int /*<<< orphan*/ ) ; 
 char* mem2hstr (char*,char*,int) ; 
 char* remcomOutBuffer ; 
 char* thread2vhstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gdbstub_report_exception(frame_context *frame,s32 thread)
{
	s32 sigval;
	char *ptr;

	ptr = remcomOutBuffer;
	sigval = computeSignal(frame->EXCPT_Number);
	*ptr++ = 'T';
	*ptr++ = highhex(sigval);
	*ptr++ = lowhex(sigval);
	*ptr++ = highhex(SP_REGNUM);
	*ptr++ = lowhex(SP_REGNUM);
	*ptr++ = ':';
	ptr = mem2hstr(ptr,(char*)&frame->GPR[1],4);
	*ptr++ = ';';
	*ptr++ = highhex(PC_REGNUM);
	*ptr++ = lowhex(PC_REGNUM);
	*ptr++ = ':';
	ptr = mem2hstr(ptr,(char*)&frame->SRR0,4);
	*ptr++ = ';';

	*ptr++ = 't';
	*ptr++ = 'h';
	*ptr++ = 'r';
	*ptr++ = 'e';
	*ptr++ = 'a';
	*ptr++ = 'd';
	*ptr++ = ':';
	ptr = thread2vhstr(ptr,thread);
	*ptr++ = ';';

	*ptr++ = '\0';

}