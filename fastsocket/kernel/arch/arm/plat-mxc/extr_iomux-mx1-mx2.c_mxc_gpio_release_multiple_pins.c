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
 int const GPIO_PIN_MASK ; 
 int const GPIO_PORT_MASK ; 
 int /*<<< orphan*/  gpio_free (unsigned int) ; 

void mxc_gpio_release_multiple_pins(const int *pin_list, int count)
{
	const int *p = pin_list;
	int i;

	for (i = 0; i < count; i++) {
		unsigned gpio = *p & (GPIO_PIN_MASK | GPIO_PORT_MASK);
		gpio_free(gpio);
		p++;
	}

}