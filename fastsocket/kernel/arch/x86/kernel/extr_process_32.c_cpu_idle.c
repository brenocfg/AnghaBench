#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS_POLLING ; 
 int /*<<< orphan*/  boot_init_stack_canary () ; 
 int /*<<< orphan*/  check_pgt_cache () ; 
 scalar_t__ cpu_is_offline (int) ; 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  play_dead () ; 
 int /*<<< orphan*/  pm_idle () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  schedule () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  start_critical_timings () ; 
 int /*<<< orphan*/  stop_critical_timings () ; 
 int /*<<< orphan*/  tick_nohz_restart_sched_tick () ; 
 int /*<<< orphan*/  tick_nohz_stop_sched_tick (int) ; 

void cpu_idle(void)
{
	int cpu = smp_processor_id();

	/*
	 * If we're the non-boot CPU, nothing set the stack canary up
	 * for us.  CPU0 already has it initialized but no harm in
	 * doing it again.  This is a good place for updating it, as
	 * we wont ever return from this function (so the invalid
	 * canaries already on the stack wont ever trigger).
	 */
	boot_init_stack_canary();

	current_thread_info()->status |= TS_POLLING;

	/* endless idle loop with no priority at all */
	while (1) {
		tick_nohz_stop_sched_tick(1);
		while (!need_resched()) {

			check_pgt_cache();
			rmb();

			if (cpu_is_offline(cpu))
				play_dead();

			local_irq_disable();
			/* Don't trace irqs off for idle */
			stop_critical_timings();
			pm_idle();
			start_critical_timings();
		}
		tick_nohz_restart_sched_tick();
		preempt_enable_no_resched();
		schedule();
		preempt_disable();
	}
}