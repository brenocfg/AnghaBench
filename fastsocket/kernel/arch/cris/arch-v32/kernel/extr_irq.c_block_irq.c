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
 int FIRST_IRQ ; 
 int REG_RD_INT_VECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WR_INT_VECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  intr_vect ; 
 int /*<<< orphan*/  irq_lock ; 
 int /*<<< orphan*/ * irq_regs ; 
 int /*<<< orphan*/  rw_mask ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
block_irq(int irq, int cpu)
{
	int intr_mask;
        unsigned long flags;

	spin_lock_irqsave(&irq_lock, flags);
	if (irq - FIRST_IRQ < 32)
		intr_mask = REG_RD_INT_VECT(intr_vect, irq_regs[cpu],
			rw_mask, 0);
	else
		intr_mask = REG_RD_INT_VECT(intr_vect, irq_regs[cpu],
			rw_mask, 1);

	/* Remember; 1 let thru, 0 block. */
	if (irq - FIRST_IRQ < 32)
		intr_mask &= ~(1 << (irq - FIRST_IRQ));
	else
		intr_mask &= ~(1 << (irq - FIRST_IRQ - 32));

	if (irq - FIRST_IRQ < 32)
		REG_WR_INT_VECT(intr_vect, irq_regs[cpu], rw_mask,
			0, intr_mask);
	else
		REG_WR_INT_VECT(intr_vect, irq_regs[cpu], rw_mask,
			1, intr_mask);
        spin_unlock_irqrestore(&irq_lock, flags);
}