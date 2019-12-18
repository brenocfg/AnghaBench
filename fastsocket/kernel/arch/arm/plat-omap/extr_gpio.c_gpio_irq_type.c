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
struct gpio_bank {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {unsigned int status; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IH_GPIO_BASE ; 
 unsigned int IH_MPUIO_BASE ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 unsigned int OMAP_MPUIO (unsigned int) ; 
 int /*<<< orphan*/  __set_irq_handler_unlocked (unsigned int,int /*<<< orphan*/ ) ; 
 int _set_gpio_triggering (struct gpio_bank*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ check_gpio (unsigned int) ; 
 int /*<<< orphan*/  cpu_class_is_omap2 () ; 
 int /*<<< orphan*/  get_gpio_index (unsigned int) ; 
 struct gpio_bank* get_irq_chip_data (unsigned int) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 TYPE_1__* irq_desc ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gpio_irq_type(unsigned irq, unsigned type)
{
	struct gpio_bank *bank;
	unsigned gpio;
	int retval;
	unsigned long flags;

	if (!cpu_class_is_omap2() && irq > IH_MPUIO_BASE)
		gpio = OMAP_MPUIO(irq - IH_MPUIO_BASE);
	else
		gpio = irq - IH_GPIO_BASE;

	if (check_gpio(gpio) < 0)
		return -EINVAL;

	if (type & ~IRQ_TYPE_SENSE_MASK)
		return -EINVAL;

	/* OMAP1 allows only only edge triggering */
	if (!cpu_class_is_omap2()
			&& (type & (IRQ_TYPE_LEVEL_LOW|IRQ_TYPE_LEVEL_HIGH)))
		return -EINVAL;

	bank = get_irq_chip_data(irq);
	spin_lock_irqsave(&bank->lock, flags);
	retval = _set_gpio_triggering(bank, get_gpio_index(gpio), type);
	if (retval == 0) {
		irq_desc[irq].status &= ~IRQ_TYPE_SENSE_MASK;
		irq_desc[irq].status |= type;
	}
	spin_unlock_irqrestore(&bank->lock, flags);

	if (type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH))
		__set_irq_handler_unlocked(irq, handle_level_irq);
	else if (type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		__set_irq_handler_unlocked(irq, handle_edge_irq);

	return retval;
}