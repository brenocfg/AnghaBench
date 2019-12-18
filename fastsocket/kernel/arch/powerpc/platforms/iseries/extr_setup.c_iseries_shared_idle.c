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
 int /*<<< orphan*/  HMT_medium () ; 
 scalar_t__ hvlpevent_is_pending () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  ppc64_runlatch_off () ; 
 int /*<<< orphan*/  ppc64_runlatch_on () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  process_iSeries_events () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  tick_nohz_restart_sched_tick () ; 
 int /*<<< orphan*/  tick_nohz_stop_sched_tick (int) ; 
 int /*<<< orphan*/  yield_shared_processor () ; 

__attribute__((used)) static void iseries_shared_idle(void)
{
	while (1) {
		tick_nohz_stop_sched_tick(1);
		while (!need_resched() && !hvlpevent_is_pending()) {
			local_irq_disable();
			ppc64_runlatch_off();

			/* Recheck with irqs off */
			if (!need_resched() && !hvlpevent_is_pending())
				yield_shared_processor();

			HMT_medium();
			local_irq_enable();
		}

		ppc64_runlatch_on();
		tick_nohz_restart_sched_tick();

		if (hvlpevent_is_pending())
			process_iSeries_events();

		preempt_enable_no_resched();
		schedule();
		preempt_disable();
	}
}