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
struct vcpu_runstate_info {size_t state; unsigned long long state_entry_time; unsigned long long* time; } ;

/* Variables and functions */
 size_t RUNSTATE_blocked ; 
 size_t RUNSTATE_running ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  get_runstate_snapshot (struct vcpu_runstate_info*) ; 
 unsigned long long ia64_native_sched_clock () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static unsigned long long xen_sched_clock(void)
{
	struct vcpu_runstate_info runstate;

	unsigned long long now;
	unsigned long long offset;
	unsigned long long ret;

	/*
	 * Ideally sched_clock should be called on a per-cpu basis
	 * anyway, so preempt should already be disabled, but that's
	 * not current practice at the moment.
	 */
	preempt_disable();

	/*
	 * both ia64_native_sched_clock() and xen's runstate are
	 * based on mAR.ITC. So difference of them makes sense.
	 */
	now = ia64_native_sched_clock();

	get_runstate_snapshot(&runstate);

	WARN_ON(runstate.state != RUNSTATE_running);

	offset = 0;
	if (now > runstate.state_entry_time)
		offset = now - runstate.state_entry_time;
	ret = runstate.time[RUNSTATE_blocked] +
		runstate.time[RUNSTATE_running] +
		offset;

	preempt_enable();

	return ret;
}