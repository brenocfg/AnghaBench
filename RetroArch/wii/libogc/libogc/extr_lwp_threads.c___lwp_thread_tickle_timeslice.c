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
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_3__ {int budget_algo; int /*<<< orphan*/  cpu_time_budget; int /*<<< orphan*/  cur_state; int /*<<< orphan*/  is_preemptible; } ;
typedef  TYPE_1__ lwp_cntrl ;

/* Variables and functions */
#define  LWP_CPU_BUDGET_ALGO_NONE 129 
#define  LWP_CPU_BUDGET_ALGO_TIMESLICE 128 
 int /*<<< orphan*/  __lwp_stateready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchdisable () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchunnest () ; 
 int /*<<< orphan*/  __lwp_thread_resettimeslice () ; 
 int /*<<< orphan*/  __lwp_wd_insert_ticks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _lwp_ticks_per_timeslice ; 
 int /*<<< orphan*/  _lwp_wd_timeslice ; 
 TYPE_1__* _thr_executing ; 
 int /*<<< orphan*/  millisecs_to_ticks (int) ; 

void __lwp_thread_tickle_timeslice(void *arg)
{
	s64 ticks;
	lwp_cntrl *exec;

	exec = _thr_executing;
	ticks = millisecs_to_ticks(1);

	__lwp_thread_dispatchdisable();

	if(!exec->is_preemptible) {
		__lwp_wd_insert_ticks(&_lwp_wd_timeslice,ticks);
		__lwp_thread_dispatchunnest();
		return;
	}
	if(!__lwp_stateready(exec->cur_state)) {
		__lwp_wd_insert_ticks(&_lwp_wd_timeslice,ticks);
		__lwp_thread_dispatchunnest();
		return;
	}

	switch(exec->budget_algo) {
		case LWP_CPU_BUDGET_ALGO_NONE:
			break;
		case LWP_CPU_BUDGET_ALGO_TIMESLICE:
			if((--exec->cpu_time_budget)==0) {
				__lwp_thread_resettimeslice();
				exec->cpu_time_budget = _lwp_ticks_per_timeslice;
			}
			break;
	}

	__lwp_wd_insert_ticks(&_lwp_wd_timeslice,ticks);
	__lwp_thread_dispatchunnest();
}