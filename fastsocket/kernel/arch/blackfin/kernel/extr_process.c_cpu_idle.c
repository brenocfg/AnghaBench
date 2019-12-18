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
 int /*<<< orphan*/  cpu_die () ; 
 scalar_t__ cpu_is_offline (int /*<<< orphan*/ ) ; 
 void default_idle () ; 
 int /*<<< orphan*/  need_resched () ; 
 void pm_idle () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  tick_nohz_restart_sched_tick () ; 
 int /*<<< orphan*/  tick_nohz_stop_sched_tick (int) ; 

void cpu_idle(void)
{
	/* endless idle loop with no priority at all */
	while (1) {
		void (*idle)(void) = pm_idle;

#ifdef CONFIG_HOTPLUG_CPU
		if (cpu_is_offline(smp_processor_id()))
			cpu_die();
#endif
		if (!idle)
			idle = default_idle;
		tick_nohz_stop_sched_tick(1);
		while (!need_resched())
			idle();
		tick_nohz_restart_sched_tick();
		preempt_enable_no_resched();
		schedule();
		preempt_disable();
	}
}