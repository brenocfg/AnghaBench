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
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_die () ; 
 scalar_t__ cpu_is_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ hlt_counter ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  led_idle_end ; 
 int /*<<< orphan*/  led_idle_start ; 
 int /*<<< orphan*/  leds_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_fiq_enable () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  pm_idle () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  start_critical_timings () ; 
 int /*<<< orphan*/  stop_critical_timings () ; 
 int /*<<< orphan*/  tick_nohz_restart_sched_tick () ; 
 int /*<<< orphan*/  tick_nohz_stop_sched_tick (int) ; 

void cpu_idle(void)
{
	local_fiq_enable();

	/* endless idle loop with no priority at all */
	while (1) {
		tick_nohz_stop_sched_tick(1);
		leds_event(led_idle_start);
		while (!need_resched()) {
#ifdef CONFIG_HOTPLUG_CPU
			if (cpu_is_offline(smp_processor_id()))
				cpu_die();
#endif

			local_irq_disable();
			if (hlt_counter) {
				local_irq_enable();
				cpu_relax();
			} else {
				stop_critical_timings();
				pm_idle();
				start_critical_timings();
				/*
				 * This will eventually be removed - pm_idle
				 * functions should always return with IRQs
				 * enabled.
				 */
				WARN_ON(irqs_disabled());
				local_irq_enable();
			}
		}
		leds_event(led_idle_end);
		tick_nohz_restart_sched_tick();
		preempt_enable_no_resched();
		schedule();
		preempt_disable();
	}
}