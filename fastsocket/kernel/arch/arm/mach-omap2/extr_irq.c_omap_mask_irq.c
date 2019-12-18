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
 scalar_t__ INTC_MIR_SET0 ; 
 unsigned int INT_34XX_GPT12_IRQ ; 
 int IRQ_BITS_PER_REG ; 
 scalar_t__ cpu_is_omap34xx () ; 
 int /*<<< orphan*/  intc_bank_write_reg (int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * irq_banks ; 
 int omap_check_spurious (unsigned int) ; 
 unsigned int previous_irq ; 

__attribute__((used)) static void omap_mask_irq(unsigned int irq)
{
	int offset = irq & (~(IRQ_BITS_PER_REG - 1));

	if (cpu_is_omap34xx()) {
		int spurious = 0;

		/*
		 * INT_34XX_GPT12_IRQ is also the spurious irq. Maybe because
		 * it is the highest irq number?
		 */
		if (irq == INT_34XX_GPT12_IRQ)
			spurious = omap_check_spurious(irq);

		if (!spurious)
			previous_irq = irq;
	}

	irq &= (IRQ_BITS_PER_REG - 1);

	intc_bank_write_reg(1 << irq, &irq_banks[0], INTC_MIR_SET0 + offset);
}