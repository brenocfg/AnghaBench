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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  dvdcmdblk ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __dvd_waitingqueue ; 
 scalar_t__ __lwp_queue_firstnodeI (int /*<<< orphan*/ *) ; 

__attribute__((used)) static dvdcmdblk* __dvd_popwaitingqueueprio(s32 prio)
{
	u32 level;
	dvdcmdblk *ret = NULL;
	_CPU_ISR_Disable(level);
	ret = (dvdcmdblk*)__lwp_queue_firstnodeI(&__dvd_waitingqueue[prio]);
	_CPU_ISR_Restore(level);
	return ret;
}