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
 int /*<<< orphan*/  block_irq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_IRQ (int,struct pt_regs*) ; 
 int /*<<< orphan*/  irq_cpu (int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  unblock_irq (int,int /*<<< orphan*/ ) ; 

void
crisv32_do_IRQ(int irq, int block, struct pt_regs* regs)
{
	/* Interrupts that may not be moved to another CPU and
         * are IRQF_DISABLED may skip blocking. This is currently
         * only valid for the timer IRQ and the IPI and is used
         * for the timer interrupt to avoid watchdog starvation.
         */
	if (!block) {
		do_IRQ(irq, regs);
		return;
	}

	block_irq(irq, smp_processor_id());
	do_IRQ(irq, regs);

	unblock_irq(irq, irq_cpu(irq));
}