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
typedef  long long s64 ;
typedef  int s32 ;
struct TYPE_4__ {int state; } ;
typedef  TYPE_1__ dvdcmdblk ;

/* Variables and functions */
 int DVD_SeekAbsAsyncPrio (TYPE_1__*,long long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_seeksynccb ; 
 int /*<<< orphan*/  __dvd_wait_queue ; 

s32 DVD_SeekPrio(dvdcmdblk *block,s64 offset,s32 prio)
{
	u32 level;
	s32 state,ret;
	if(offset>0 && offset<8511160320LL) {
		ret = DVD_SeekAbsAsyncPrio(block,offset,__dvd_seeksynccb,prio);
		if(!ret) return -1;

		_CPU_ISR_Disable(level);
		do {
			state = block->state;
			if(state==0) ret = 0;
			else if(state==-1) ret = -1;
			else if(state==10) ret = -3;
			else LWP_ThreadSleep(__dvd_wait_queue);
		} while(state!=0 && state!=-1 && state!=10);
		_CPU_ISR_Restore(level);

		return ret;
	}
	return -1;
}