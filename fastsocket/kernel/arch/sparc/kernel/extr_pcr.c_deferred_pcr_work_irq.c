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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int PIL_DEFERRED_PCR_WORK ; 
 int /*<<< orphan*/  clear_softint (int) ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  perf_event_do_pending () ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 

void deferred_pcr_work_irq(int irq, struct pt_regs *regs)
{
	struct pt_regs *old_regs;

	clear_softint(1 << PIL_DEFERRED_PCR_WORK);

	old_regs = set_irq_regs(regs);
	irq_enter();
#ifdef CONFIG_PERF_EVENTS
	perf_event_do_pending();
#endif
	irq_exit();
	set_irq_regs(old_regs);
}