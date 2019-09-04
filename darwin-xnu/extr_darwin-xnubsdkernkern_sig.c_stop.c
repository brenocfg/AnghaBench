#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_5__ {scalar_t__ p_stat; int /*<<< orphan*/  task; int /*<<< orphan*/  p_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSBitAndAtomic (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* PROC_NULL ; 
 scalar_t__ P_CONTINUED ; 
 scalar_t__ SSTOP ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  task_suspend_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
stop(proc_t p, proc_t parent)
{
	OSBitAndAtomic(~((uint32_t)P_CONTINUED), &p->p_flag);
	if ((parent != PROC_NULL) && (parent->p_stat != SSTOP)) {
		proc_list_lock();
		wakeup((caddr_t)parent);
		proc_list_unlock();
	}
	(void) task_suspend_internal(p->task);
}