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
 int /*<<< orphan*/  ep93xx_gpio_update_int_params (int) ; 
 int* gpio_int_unmasked ; 
 int irq_to_gpio (unsigned int) ; 

__attribute__((used)) static void ep93xx_gpio_irq_mask(unsigned int irq)
{
	int line = irq_to_gpio(irq);
	int port = line >> 3;

	gpio_int_unmasked[port] &= ~(1 << (line & 7));
	ep93xx_gpio_update_int_params(port);
}