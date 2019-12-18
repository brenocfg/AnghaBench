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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  concurrent_irq ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 unsigned int get_irq (struct pt_regs*) ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 

void do_IRQ(struct pt_regs *regs)
{
	unsigned int irq;
	struct pt_regs *old_regs = set_irq_regs(regs);

	irq_enter();
	irq = get_irq(regs);
next_irq:
	BUG_ON(irq == -1U);
	generic_handle_irq(irq);

	irq = get_irq(regs);
	if (irq != -1U) {
		pr_debug("next irq: %d\n", irq);
		++concurrent_irq;
		goto next_irq;
	}

	irq_exit();
	set_irq_regs(old_regs);
}