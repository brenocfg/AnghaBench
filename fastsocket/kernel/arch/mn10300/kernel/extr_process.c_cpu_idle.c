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
struct TYPE_2__ {int /*<<< orphan*/  idle_timestamp; } ;

/* Variables and functions */
 void default_idle () ; 
 TYPE_1__* irq_stat ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  need_resched () ; 
 void pm_idle () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  schedule () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  smp_rmb () ; 

void cpu_idle(void)
{
	int cpu = smp_processor_id();

	/* endless idle loop with no priority at all */
	for (;;) {
		while (!need_resched()) {
			void (*idle)(void);

			smp_rmb();
			idle = pm_idle;
			if (!idle)
				idle = default_idle;

			irq_stat[cpu].idle_timestamp = jiffies;
			idle();
		}

		preempt_enable_no_resched();
		schedule();
		preempt_disable();
	}
}