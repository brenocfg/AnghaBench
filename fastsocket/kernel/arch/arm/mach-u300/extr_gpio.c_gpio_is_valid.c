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
 int U300_GPIO_NUM_PORTS ; 
 int U300_GPIO_PINS_PER_PORT ; 

int gpio_is_valid(int number)
{
	if (number >= 0 &&
	    number < (U300_GPIO_NUM_PORTS * U300_GPIO_PINS_PER_PORT))
		return 1;
	return 0;
}