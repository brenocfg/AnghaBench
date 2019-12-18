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
 int /*<<< orphan*/  HMT_low () ; 
 int /*<<< orphan*/  HMT_medium () ; 
 int /*<<< orphan*/  TIF_POLLING_NRFLAG ; 
 scalar_t__ hvlpevent_is_pending () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  ppc64_runlatch_off () ; 
 int /*<<< orphan*/  ppc64_runlatch_on () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  process_iSeries_events () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_nohz_restart_sched_tick () ; 
 int /*<<< orphan*/  tick_nohz_stop_sched_tick (int) ; 

__attribute__((used)) static void iseries_dedicated_idle(void)
{
	set_thread_flag(TIF_POLLING_NRFLAG);

	while (1) {
		tick_nohz_stop_sched_tick(1);
		if (!need_resched()) {
			while (!need_resched()) {
				ppc64_runlatch_off();
				HMT_low();

				if (hvlpevent_is_pending()) {
					HMT_medium();
					ppc64_runlatch_on();
					process_iSeries_events();
				}
			}

			HMT_medium();
		}

		ppc64_runlatch_on();
		tick_nohz_restart_sched_tick();
		preempt_enable_no_resched();
		schedule();
		preempt_disable();
	}
}