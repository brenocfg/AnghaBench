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
 int IRQ_BANK (int) ; 
 int IRQ_BIT (int) ; 
 int IRQ_ILR0_REG_OFFSET ; 
 int /*<<< orphan*/  irq_bank_writel (unsigned long,int,unsigned long) ; 

__attribute__((used)) static void omap_irq_set_cfg(int irq, int fiq, int priority, int trigger)
{
	signed int bank;
	unsigned long val, offset;

	bank = IRQ_BANK(irq);
	/* FIQ is only available on bank 0 interrupts */
	fiq = bank ? 0 : (fiq & 0x1);
	val = fiq | ((priority & 0x1f) << 2) | ((trigger & 0x1) << 1);
	offset = IRQ_ILR0_REG_OFFSET + IRQ_BIT(irq) * 0x4;
	irq_bank_writel(val, bank, offset);
}