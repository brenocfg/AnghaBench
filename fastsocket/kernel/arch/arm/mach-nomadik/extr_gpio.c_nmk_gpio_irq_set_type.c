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
typedef  int /*<<< orphan*/  u32 ;
struct nmk_gpio_chip {int /*<<< orphan*/  lock; scalar_t__ addr; int /*<<< orphan*/  edge_falling; int /*<<< orphan*/  edge_rising; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 scalar_t__ NMK_GPIO_FIMSC ; 
 scalar_t__ NMK_GPIO_RIMSC ; 
 int NOMADIK_IRQ_TO_GPIO (unsigned int) ; 
 struct nmk_gpio_chip* get_irq_chip_data (unsigned int) ; 
 int /*<<< orphan*/  nmk_gpio_get_bitmask (int) ; 
 int /*<<< orphan*/  nmk_gpio_irq_unmask (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int nmk_gpio_irq_set_type(unsigned int irq, unsigned int type)
{
	int gpio;
	struct nmk_gpio_chip *nmk_chip;
	unsigned long flags;
	u32 bitmask;

	gpio = NOMADIK_IRQ_TO_GPIO(irq);
	nmk_chip = get_irq_chip_data(irq);
	bitmask = nmk_gpio_get_bitmask(gpio);
	if (!nmk_chip)
		return -EINVAL;

	if (type & IRQ_TYPE_LEVEL_HIGH)
		return -EINVAL;
	if (type & IRQ_TYPE_LEVEL_LOW)
		return -EINVAL;

	spin_lock_irqsave(&nmk_chip->lock, flags);

	nmk_chip->edge_rising &= ~bitmask;
	if (type & IRQ_TYPE_EDGE_RISING)
		nmk_chip->edge_rising |= bitmask;
	writel(nmk_chip->edge_rising, nmk_chip->addr + NMK_GPIO_RIMSC);

	nmk_chip->edge_falling &= ~bitmask;
	if (type & IRQ_TYPE_EDGE_FALLING)
		nmk_chip->edge_falling |= bitmask;
	writel(nmk_chip->edge_falling, nmk_chip->addr + NMK_GPIO_FIMSC);

	spin_unlock_irqrestore(&nmk_chip->lock, flags);

	nmk_gpio_irq_unmask(irq);

	return 0;
}