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
typedef  int s32 ;
typedef  int /*<<< orphan*/  lwp_t ;
struct TYPE_4__ {int /*<<< orphan*/  cur_state; } ;
typedef  TYPE_1__ lwp_cntrl ;

/* Variables and functions */
 int LWP_ALREADY_SUSPENDED ; 
 int LWP_SUCCESSFUL ; 
 TYPE_1__* __lwp_cntrl_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_statesuspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 int /*<<< orphan*/  __lwp_thread_suspend (TYPE_1__*) ; 

s32 LWP_SuspendThread(lwp_t thethread)
{
	lwp_cntrl *lwp_thread;

	lwp_thread = __lwp_cntrl_open(thethread);
	if(!lwp_thread) return -1;

	if(!__lwp_statesuspended(lwp_thread->cur_state)) {
		__lwp_thread_suspend(lwp_thread);
		__lwp_thread_dispatchenable();
		return LWP_SUCCESSFUL;
	}
	__lwp_thread_dispatchenable();
	return LWP_ALREADY_SUSPENDED;
}