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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int at91_get_gpio_value (int) ; 
 int /*<<< orphan*/  ide_intr (int,void*) ; 

irqreturn_t at91_irq_handler(int irq, void *dev_id)
{
	int ntries = 8;
	int pin_val1, pin_val2;

	/* additional deglitch, line can be noisy in badly designed PCB */
	do {
		pin_val1 = at91_get_gpio_value(irq);
		pin_val2 = at91_get_gpio_value(irq);
	} while (pin_val1 != pin_val2 && --ntries > 0);

	if (pin_val1 == 0 || ntries <= 0)
		return IRQ_HANDLED;

	return ide_intr(irq, dev_id);
}