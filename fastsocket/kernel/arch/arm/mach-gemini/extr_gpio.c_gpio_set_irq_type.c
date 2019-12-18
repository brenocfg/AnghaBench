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
 int EINVAL ; 
 unsigned int GPIO_BASE (unsigned int) ; 
 scalar_t__ GPIO_INT_BOTH_EDGE ; 
 scalar_t__ GPIO_INT_TYPE ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  gpio_ack_irq (unsigned int) ; 
 unsigned int irq_to_gpio (unsigned int) ; 

__attribute__((used)) static int gpio_set_irq_type(unsigned int irq, unsigned int type)
{
	unsigned int gpio = irq_to_gpio(irq);
	unsigned int gpio_mask = 1 << (gpio % 32);
	unsigned int base = GPIO_BASE(gpio / 32);
	unsigned int reg_both, reg_level, reg_type;

	reg_type = __raw_readl(base + GPIO_INT_TYPE);
	reg_level = __raw_readl(base + GPIO_INT_BOTH_EDGE);
	reg_both = __raw_readl(base + GPIO_INT_BOTH_EDGE);

	switch (type) {
	case IRQ_TYPE_EDGE_BOTH:
		reg_type &= ~gpio_mask;
		reg_both |= gpio_mask;
		break;
	case IRQ_TYPE_EDGE_RISING:
		reg_type &= ~gpio_mask;
		reg_both &= ~gpio_mask;
		reg_level &= ~gpio_mask;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		reg_type &= ~gpio_mask;
		reg_both &= ~gpio_mask;
		reg_level |= gpio_mask;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		reg_type |= gpio_mask;
		reg_level &= ~gpio_mask;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		reg_type |= gpio_mask;
		reg_level |= gpio_mask;
		break;
	default:
		return -EINVAL;
	}

	__raw_writel(reg_type, base + GPIO_INT_TYPE);
	__raw_writel(reg_level, base + GPIO_INT_BOTH_EDGE);
	__raw_writel(reg_both, base + GPIO_INT_BOTH_EDGE);

	gpio_ack_irq(irq);

	return 0;
}