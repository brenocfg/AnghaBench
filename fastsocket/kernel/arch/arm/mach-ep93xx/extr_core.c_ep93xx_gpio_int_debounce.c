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
 int /*<<< orphan*/  EP93XX_GPIO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 int* gpio_int_debounce ; 
 int /*<<< orphan*/ * int_debounce_register_offset ; 
 int irq_to_gpio (unsigned int) ; 

void ep93xx_gpio_int_debounce(unsigned int irq, int enable)
{
	int line = irq_to_gpio(irq);
	int port = line >> 3;
	int port_mask = 1 << (line & 7);

	if (enable)
		gpio_int_debounce[port] |= port_mask;
	else
		gpio_int_debounce[port] &= ~port_mask;

	__raw_writeb(gpio_int_debounce[port],
		EP93XX_GPIO_REG(int_debounce_register_offset[port]));
}