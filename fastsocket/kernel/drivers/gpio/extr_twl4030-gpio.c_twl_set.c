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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int TWL4030_GPIO_MAX ; 
 int /*<<< orphan*/  twl4030_led_set_value (unsigned int,int) ; 
 int /*<<< orphan*/  twl4030_set_gpio_dataout (unsigned int,int) ; 

__attribute__((used)) static void twl_set(struct gpio_chip *chip, unsigned offset, int value)
{
	if (offset < TWL4030_GPIO_MAX)
		twl4030_set_gpio_dataout(offset, value);
	else
		twl4030_led_set_value(offset - TWL4030_GPIO_MAX, value);
}