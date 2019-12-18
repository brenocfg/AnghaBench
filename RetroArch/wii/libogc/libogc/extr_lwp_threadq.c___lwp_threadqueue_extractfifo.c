#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lwp_thrqueue ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
struct TYPE_6__ {int /*<<< orphan*/  timer; TYPE_1__ object; int /*<<< orphan*/  cur_state; } ;
typedef  TYPE_2__ lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_queue_extractI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_statewaitthreadqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_unblock (TYPE_2__*) ; 
 int /*<<< orphan*/  __lwp_wd_deactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_wd_isactive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_wd_remove_ticks (int /*<<< orphan*/ *) ; 

void __lwp_threadqueue_extractfifo(lwp_thrqueue *queue,lwp_cntrl *thethread)
{
	u32 level;

	_CPU_ISR_Disable(level);
	if(!__lwp_statewaitthreadqueue(thethread->cur_state)) {
		_CPU_ISR_Restore(level);
		return;
	}

	__lwp_queue_extractI(&thethread->object.node);
	if(!__lwp_wd_isactive(&thethread->timer)) {
		_CPU_ISR_Restore(level);
	} else {
		__lwp_wd_deactivate(&thethread->timer);
		_CPU_ISR_Restore(level);
		__lwp_wd_remove_ticks(&thethread->timer);
	}
	__lwp_thread_unblock(thethread);
}