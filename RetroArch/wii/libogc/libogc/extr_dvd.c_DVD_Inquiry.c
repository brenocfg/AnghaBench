#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  dvddrvinfo ;
struct TYPE_4__ {int state; int txdsize; } ;
typedef  TYPE_1__ dvdcmdblk ;

/* Variables and functions */
 int DVD_InquiryAsync (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_inquirysynccb ; 
 int /*<<< orphan*/  __dvd_wait_queue ; 

s32 DVD_Inquiry(dvdcmdblk *block,dvddrvinfo *info)
{
	u32 level;
	s32 state,ret;
	ret = DVD_InquiryAsync(block,info,__dvd_inquirysynccb);
	if(!ret) return -1;

	_CPU_ISR_Disable(level);
	do {
		state = block->state;
		if(state==0) ret = block->txdsize;
		else if(state==-1) ret = -1;
		else if(state==10) ret = -3;
		else LWP_ThreadSleep(__dvd_wait_queue);
	} while(state!=0 && state!=-1 && state!=10);
	_CPU_ISR_Restore(level);
	return ret;
}