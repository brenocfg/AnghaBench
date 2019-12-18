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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ base_reg; } ;

/* Variables and functions */
 int IRQ_BANK (unsigned int) ; 
 int IRQ_BIT (unsigned int) ; 
 scalar_t__ IRQ_MIR_REG_OFFSET ; 
 TYPE_1__* irq_banks ; 
 int omap_readl (scalar_t__) ; 
 int /*<<< orphan*/  omap_writel (int,scalar_t__) ; 

__attribute__((used)) static void omap_mask_irq(unsigned int irq)
{
	int bank = IRQ_BANK(irq);
	u32 l;

	l = omap_readl(irq_banks[bank].base_reg + IRQ_MIR_REG_OFFSET);
	l |= 1 << IRQ_BIT(irq);
	omap_writel(l, irq_banks[bank].base_reg + IRQ_MIR_REG_OFFSET);
}