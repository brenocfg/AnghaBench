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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int GPIO_BASE (unsigned int) ; 
 scalar_t__ GPIO_DIR ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void _set_gpio_direction(struct gpio_chip *chip, unsigned offset,
				int dir)
{
	unsigned int base = GPIO_BASE(offset / 32);
	unsigned int reg;

	reg = __raw_readl(base + GPIO_DIR);
	if (dir)
		reg |= 1 << (offset % 32);
	else
		reg &= ~(1 << (offset % 32));
	__raw_writel(reg, base + GPIO_DIR);
}