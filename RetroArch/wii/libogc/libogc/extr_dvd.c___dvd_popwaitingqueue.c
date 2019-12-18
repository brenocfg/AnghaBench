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
typedef  int u32 ;
typedef  int /*<<< orphan*/  dvdcmdblk ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int /*<<< orphan*/ * __dvd_popwaitingqueueprio (int) ; 
 int /*<<< orphan*/ * __dvd_waitingqueue ; 
 int /*<<< orphan*/  __lwp_queue_isempty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static dvdcmdblk* __dvd_popwaitingqueue()
{
	u32 i,level;
	dvdcmdblk *ret = NULL;
	_CPU_ISR_Disable(level);
	for(i=0;i<4;i++) {
		if(!__lwp_queue_isempty(&__dvd_waitingqueue[i])) {
			_CPU_ISR_Restore(level);
			ret = __dvd_popwaitingqueueprio(i);
			return ret;
		}
	}
	_CPU_ISR_Restore(level);
	return NULL;
}