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
 int /*<<< orphan*/  TIF_POLLING_NRFLAG ; 
 scalar_t__ cpu_is_offline (int) ; 
 int /*<<< orphan*/  cpu_play_dead () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  sparc64_yield (int) ; 
 int /*<<< orphan*/  tick_nohz_restart_sched_tick () ; 
 int /*<<< orphan*/  tick_nohz_stop_sched_tick (int) ; 

void cpu_idle(void)
{
	int cpu = smp_processor_id();

	set_thread_flag(TIF_POLLING_NRFLAG);

	while(1) {
		tick_nohz_stop_sched_tick(1);

		while (!need_resched() && !cpu_is_offline(cpu))
			sparc64_yield(cpu);

		tick_nohz_restart_sched_tick();

		preempt_enable_no_resched();

#ifdef CONFIG_HOTPLUG_CPU
		if (cpu_is_offline(cpu))
			cpu_play_dead();
#endif

		schedule();
		preempt_disable();
	}
}