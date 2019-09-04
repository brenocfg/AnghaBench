#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_7__ {scalar_t__ sched_mode; int base_pri; int state; scalar_t__ last_made_runnable_time; scalar_t__ last_basepri_change_time; } ;

/* Variables and functions */
 int BASEPRI_RTQUEUES ; 
 int MINPRI ; 
 int /*<<< orphan*/  PERFCONTROL_ATTR_UPDATE ; 
 int /*<<< orphan*/  PERFCONTROL_CALLOUT_WAKE_UNSAFE ; 
 int /*<<< orphan*/  SETPRI_DEFAULT ; 
 scalar_t__ THREAD_NOT_RUNNABLE ; 
 scalar_t__ TH_MODE_REALTIME ; 
 int TH_RUN ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 scalar_t__ mach_approximate_time () ; 
 int /*<<< orphan*/  machine_switch_perfcontrol_state_update (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sched_update_thread_bucket (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_recompute_sched_pri (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
sched_set_thread_base_priority(thread_t thread, int priority)
{
	assert(priority >= MINPRI);
	uint64_t ctime = 0;

	if (thread->sched_mode == TH_MODE_REALTIME)
		assert(priority <= BASEPRI_RTQUEUES);
	else
		assert(priority < BASEPRI_RTQUEUES);

	int old_base_pri = thread->base_pri;
	thread->base_pri = priority;

	if ((thread->state & TH_RUN) == TH_RUN) {
		assert(thread->last_made_runnable_time != THREAD_NOT_RUNNABLE);
		ctime = mach_approximate_time();
		thread->last_basepri_change_time = ctime;
	} else {
		assert(thread->last_basepri_change_time == THREAD_NOT_RUNNABLE);
		assert(thread->last_made_runnable_time == THREAD_NOT_RUNNABLE);
	}

	/* 
	 * Currently the perfcontrol_attr depends on the base pri of the 
	 * thread. Therefore, we use this function as the hook for the 
	 * perfcontrol callout. 
	 */
	if (thread == current_thread() && old_base_pri != priority) {
		if (!ctime) {
		    ctime = mach_approximate_time();
		}
		machine_switch_perfcontrol_state_update(PERFCONTROL_ATTR_UPDATE,
			ctime, PERFCONTROL_CALLOUT_WAKE_UNSAFE, thread);
	}
	sched_update_thread_bucket(thread);

	thread_recompute_sched_pri(thread, SETPRI_DEFAULT);
}