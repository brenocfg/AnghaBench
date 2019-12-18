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
 int GPIO_IN ; 
 int GPIO_IRQ_falling_edge ; 
 int GPIO_IRQ_level_high ; 
 int GPIO_IRQ_level_low ; 
 int GPIO_IRQ_rising_edge ; 
 int GPIO_OUT ; 
 int /*<<< orphan*/  IXP2000_GPIO_PDCR ; 
 int /*<<< orphan*/  IXP2000_GPIO_PDSR ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  update_gpio_int_csrs () ; 

void gpio_line_config(int line, int direction)
{
	unsigned long flags;

	local_irq_save(flags);
	if (direction == GPIO_OUT) {
		/* if it's an output, it ain't an interrupt anymore */
		GPIO_IRQ_falling_edge &= ~(1 << line);
		GPIO_IRQ_rising_edge &= ~(1 << line);
		GPIO_IRQ_level_low &= ~(1 << line);
		GPIO_IRQ_level_high &= ~(1 << line);
		update_gpio_int_csrs();

		ixp2000_reg_wrb(IXP2000_GPIO_PDSR, 1 << line);
	} else if (direction == GPIO_IN) {
		ixp2000_reg_wrb(IXP2000_GPIO_PDCR, 1 << line);
	}
	local_irq_restore(flags);
}