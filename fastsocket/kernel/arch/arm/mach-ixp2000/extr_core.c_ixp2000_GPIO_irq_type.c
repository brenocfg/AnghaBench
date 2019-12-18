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
 int GPIO_IRQ_falling_edge ; 
 int GPIO_IRQ_level_high ; 
 int GPIO_IRQ_level_low ; 
 int GPIO_IRQ_rising_edge ; 
 unsigned int IRQ_IXP2000_GPIO0 ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 int /*<<< orphan*/  IXP2000_GPIO_PDCR ; 
 int /*<<< orphan*/  ixp2000_reg_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_gpio_int_csrs () ; 

__attribute__((used)) static int ixp2000_GPIO_irq_type(unsigned int irq, unsigned int type)
{
	int line = irq - IRQ_IXP2000_GPIO0;

	/*
	 * First, configure this GPIO line as an input.
	 */
	ixp2000_reg_write(IXP2000_GPIO_PDCR, 1 << line);

	/*
	 * Then, set the proper trigger type.
	 */
	if (type & IRQ_TYPE_EDGE_FALLING)
		GPIO_IRQ_falling_edge |= 1 << line;
	else
		GPIO_IRQ_falling_edge &= ~(1 << line);
	if (type & IRQ_TYPE_EDGE_RISING)
		GPIO_IRQ_rising_edge |= 1 << line;
	else
		GPIO_IRQ_rising_edge &= ~(1 << line);
	if (type & IRQ_TYPE_LEVEL_LOW)
		GPIO_IRQ_level_low |= 1 << line;
	else
		GPIO_IRQ_level_low &= ~(1 << line);
	if (type & IRQ_TYPE_LEVEL_HIGH)
		GPIO_IRQ_level_high |= 1 << line;
	else
		GPIO_IRQ_level_high &= ~(1 << line);
	update_gpio_int_csrs();

	return 0;
}