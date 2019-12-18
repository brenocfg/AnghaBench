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
typedef  unsigned int u32 ;

/* Variables and functions */
 int IRQ_BIT (unsigned int) ; 
 int /*<<< orphan*/  IRQ_ENT_REG0_OFFSET ; 
 int /*<<< orphan*/  IRQ_ENT_REG1_OFFSET ; 
 unsigned int davinci_irq_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_irq_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void davinci_mask_irq(unsigned int irq)
{
	unsigned int mask;
	u32 l;

	mask = 1 << IRQ_BIT(irq);

	if (irq > 31) {
		l = davinci_irq_readl(IRQ_ENT_REG1_OFFSET);
		l &= ~mask;
		davinci_irq_writel(l, IRQ_ENT_REG1_OFFSET);
	} else {
		l = davinci_irq_readl(IRQ_ENT_REG0_OFFSET);
		l &= ~mask;
		davinci_irq_writel(l, IRQ_ENT_REG0_OFFSET);
	}
}