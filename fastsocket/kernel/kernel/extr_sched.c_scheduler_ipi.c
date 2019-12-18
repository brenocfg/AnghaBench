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
 int /*<<< orphan*/  SCHED_SOFTIRQ ; 
 scalar_t__ got_nohz_idle_kick () ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  raise_softirq_irqoff (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void scheduler_ipi(void)
{
	if (!got_nohz_idle_kick())
		return;

	/*
	 * Not all reschedule IPI handlers call irq_enter/irq_exit, since
	 * traditionally all their work was done from the interrupt return
	 * path. Now that we actually do some work, we need to make sure
	 * we do call them.
	 *
	 * Some archs already do call them, luckily irq_enter/exit nest
	 * properly.
	 *
	 * Arguably we should visit all archs and update all handlers,
	 * however a fair share of IPIs are still resched only so this would
	 * somewhat pessimize the simple resched case.
	 */
	irq_enter();
	/*
	 * Check if someone kicked us for doing the nohz idle load balance.
	 */
	if (unlikely(got_nohz_idle_kick() && !need_resched()))
		raise_softirq_irqoff(SCHED_SOFTIRQ);
	irq_exit();
}