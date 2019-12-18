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
struct TYPE_4__ {int state; int txdsize; } ;
typedef  TYPE_1__ dvdcmdblk ;

/* Variables and functions */
 int DVD_ControlDriveAsync (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_motorcntrlsynccb ; 
 int /*<<< orphan*/  __dvd_wait_queue ; 

s32 DVD_ControlDrive(dvdcmdblk *block,u32 cmd)
{
	s32 ret,state;
	u32 level;
	ret = DVD_ControlDriveAsync(block,cmd,__dvd_motorcntrlsynccb);

	_CPU_ISR_Disable(level);
	do {
		state = block->state;
		if(state==0 || state==-1) ret = -1;
		else if(state==10) ret = block->txdsize;
		else LWP_ThreadSleep(__dvd_wait_queue);
	} while(state!=0 && state!=-1 && state!=10);
	_CPU_ISR_Restore(level);

	return ret;
}