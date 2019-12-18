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
 int IRQ_BIT (unsigned int) ; 
 int /*<<< orphan*/  IRQ_REG0_OFFSET ; 
 int /*<<< orphan*/  IRQ_REG1_OFFSET ; 
 int /*<<< orphan*/  davinci_irq_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void davinci_ack_irq(unsigned int irq)
{
	unsigned int mask;

	mask = 1 << IRQ_BIT(irq);

	if (irq > 31)
		davinci_irq_writel(mask, IRQ_REG1_OFFSET);
	else
		davinci_irq_writel(mask, IRQ_REG0_OFFSET);
}