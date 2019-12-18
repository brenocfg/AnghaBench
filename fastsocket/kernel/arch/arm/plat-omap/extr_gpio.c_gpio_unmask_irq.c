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
typedef  int u32 ;
struct irq_desc {int status; } ;
struct gpio_bank {unsigned int level_mask; } ;

/* Variables and functions */
 unsigned int IH_GPIO_BASE ; 
 int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  _clear_gpio_irqstatus (struct gpio_bank*,unsigned int) ; 
 int /*<<< orphan*/  _set_gpio_irqenable (struct gpio_bank*,unsigned int,int) ; 
 int /*<<< orphan*/  _set_gpio_triggering (struct gpio_bank*,int,int) ; 
 int get_gpio_index (unsigned int) ; 
 struct gpio_bank* get_irq_chip_data (unsigned int) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 

__attribute__((used)) static void gpio_unmask_irq(unsigned int irq)
{
	unsigned int gpio = irq - IH_GPIO_BASE;
	struct gpio_bank *bank = get_irq_chip_data(irq);
	unsigned int irq_mask = 1 << get_gpio_index(gpio);
	struct irq_desc *desc = irq_to_desc(irq);
	u32 trigger = desc->status & IRQ_TYPE_SENSE_MASK;

	if (trigger)
		_set_gpio_triggering(bank, get_gpio_index(gpio), trigger);

	/* For level-triggered GPIOs, the clearing must be done after
	 * the HW source is cleared, thus after the handler has run */
	if (bank->level_mask & irq_mask) {
		_set_gpio_irqenable(bank, gpio, 0);
		_clear_gpio_irqstatus(bank, gpio);
	}

	_set_gpio_irqenable(bank, gpio, 1);
}