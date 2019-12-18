#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_14__ {int /*<<< orphan*/  information; } ;
struct TYPE_12__ {scalar_t__ ret_arg; } ;
struct TYPE_13__ {TYPE_9__ object; int /*<<< orphan*/  budget_algo; scalar_t__ cpu_time_budget; TYPE_1__ wait; int /*<<< orphan*/  join_list; int /*<<< orphan*/  timer; } ;
typedef  TYPE_2__ lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_CPU_BUDGET_ALGO_NONE ; 
 int /*<<< orphan*/  LWP_STATES_TRANSIENT ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __libc_delete_hook (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  __lwp_objmgr_close (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  __lwp_objmgr_free (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  __lwp_stack_free (TYPE_2__*) ; 
 int /*<<< orphan*/  __lwp_thread_deallocatefp () ; 
 scalar_t__ __lwp_thread_isallocatedfp (TYPE_2__*) ; 
 int /*<<< orphan*/  __lwp_thread_setstate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* __lwp_threadqueue_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_threadqueue_extractproxy (TYPE_2__*) ; 
 scalar_t__ __lwp_wd_isactive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_wd_remove_ticks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _thr_executing ; 

void __lwp_thread_close(lwp_cntrl *thethread)
{
	u32 level;
	void **value_ptr;
	lwp_cntrl *p;

	__lwp_thread_setstate(thethread,LWP_STATES_TRANSIENT);

	if(!__lwp_threadqueue_extractproxy(thethread)) {
		if(__lwp_wd_isactive(&thethread->timer))
			__lwp_wd_remove_ticks(&thethread->timer);
	}

	_CPU_ISR_Disable(level);
	value_ptr = (void**)thethread->wait.ret_arg;
	while((p=__lwp_threadqueue_dequeue(&thethread->join_list))!=NULL) {
		*(void**)p->wait.ret_arg = value_ptr;
	}
	thethread->cpu_time_budget = 0;
	thethread->budget_algo = LWP_CPU_BUDGET_ALGO_NONE;
	_CPU_ISR_Restore(level);

	__libc_delete_hook(_thr_executing,thethread);

	if(__lwp_thread_isallocatedfp(thethread))
		__lwp_thread_deallocatefp();

	__lwp_stack_free(thethread);

	__lwp_objmgr_close(thethread->object.information,&thethread->object);
	__lwp_objmgr_free(thethread->object.information,&thethread->object);
}