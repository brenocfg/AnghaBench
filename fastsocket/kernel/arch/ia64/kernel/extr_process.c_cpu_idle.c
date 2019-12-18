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
 scalar_t__ can_do_pal_halt ; 
 int /*<<< orphan*/  check_pgt_cache () ; 
 scalar_t__ cpu_is_offline (int) ; 
 TYPE_1__* current_thread_info () ; 
 void default_idle () ; 
 void ia64_mark_idle (int) ; 
 int /*<<< orphan*/  min_xtp () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  normal_xtp () ; 
 int /*<<< orphan*/  play_dead () ; 
 void pm_idle () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int smp_processor_id () ; 
 void stub1 (int) ; 
 void stub2 () ; 
 void stub3 (int) ; 

void __attribute__((noreturn))
cpu_idle (void)
{
	void (*mark_idle)(int) = ia64_mark_idle;
  	int cpu = smp_processor_id();

	/* endless idle loop with no priority at all */
	while (1) {
		if (can_do_pal_halt) {
			current_thread_info()->status &= ~TS_POLLING;
			/*
			 * TS_POLLING-cleared state must be visible before we
			 * test NEED_RESCHED:
			 */
			smp_mb();
		} else {
			current_thread_info()->status |= TS_POLLING;
		}

		if (!need_resched()) {
			void (*idle)(void);
#ifdef CONFIG_SMP
			min_xtp();
#endif
			rmb();
			if (mark_idle)
				(*mark_idle)(1);

			idle = pm_idle;
			if (!idle)
				idle = default_idle;
			(*idle)();
			if (mark_idle)
				(*mark_idle)(0);
#ifdef CONFIG_SMP
			normal_xtp();
#endif
		}
		preempt_enable_no_resched();
		schedule();
		preempt_disable();
		check_pgt_cache();
		if (cpu_is_offline(cpu))
			play_dead();
	}
}