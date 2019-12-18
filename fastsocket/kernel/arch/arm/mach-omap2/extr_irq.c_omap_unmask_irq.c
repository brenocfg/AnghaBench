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
 scalar_t__ INTC_MIR_CLEAR0 ; 
 int IRQ_BITS_PER_REG ; 
 int /*<<< orphan*/  intc_bank_write_reg (int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * irq_banks ; 

__attribute__((used)) static void omap_unmask_irq(unsigned int irq)
{
	int offset = irq & (~(IRQ_BITS_PER_REG - 1));

	irq &= (IRQ_BITS_PER_REG - 1);

	intc_bank_write_reg(1 << irq, &irq_banks[0], INTC_MIR_CLEAR0 + offset);
}