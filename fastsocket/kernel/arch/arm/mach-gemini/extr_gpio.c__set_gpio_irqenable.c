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
 scalar_t__ GPIO_INT_EN ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void _set_gpio_irqenable(unsigned int base, unsigned int index,
				int enable)
{
	unsigned int reg;

	reg = __raw_readl(base + GPIO_INT_EN);
	reg = (reg & (~(1 << index))) | (!!enable << index);
	__raw_writel(reg, base + GPIO_INT_EN);
}