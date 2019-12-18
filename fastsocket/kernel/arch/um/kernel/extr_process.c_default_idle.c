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

/* Variables and functions */
 unsigned long long disable_timer () ; 
 int /*<<< orphan*/  idle_sleep (unsigned long long) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  tick_nohz_restart_sched_tick () ; 
 int /*<<< orphan*/  tick_nohz_stop_sched_tick (int) ; 

void default_idle(void)
{
	unsigned long long nsecs;

	while (1) {
		/* endless idle loop with no priority at all */

		/*
		 * although we are an idle CPU, we do not want to
		 * get into the scheduler unnecessarily.
		 */
		if (need_resched())
			schedule();

		tick_nohz_stop_sched_tick(1);
		nsecs = disable_timer();
		idle_sleep(nsecs);
		tick_nohz_restart_sched_tick();
	}
}