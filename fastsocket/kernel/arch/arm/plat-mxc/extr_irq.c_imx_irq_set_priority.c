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
 scalar_t__ AVIC_NIPRIORITY (unsigned char) ; 
 int EINVAL ; 
 int ENOSYS ; 
 unsigned char MXC_INTERNAL_IRQS ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 scalar_t__ avic_base ; 

int imx_irq_set_priority(unsigned char irq, unsigned char prio)
{
#ifdef CONFIG_MXC_IRQ_PRIOR
	unsigned int temp;
	unsigned int mask = 0x0F << irq % 8 * 4;

	if (irq >= MXC_INTERNAL_IRQS)
		return -EINVAL;;

	temp = __raw_readl(avic_base + AVIC_NIPRIORITY(irq / 8));
	temp &= ~mask;
	temp |= prio & mask;

	__raw_writel(temp, avic_base + AVIC_NIPRIORITY(irq / 8));

	return 0;
#else
	return -ENOSYS;
#endif
}