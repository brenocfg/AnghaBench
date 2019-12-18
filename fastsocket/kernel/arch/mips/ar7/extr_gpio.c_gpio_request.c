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
 unsigned int AR7_GPIO_MAX ; 
 int EBUSY ; 
 int EINVAL ; 
 char const** ar7_gpio_list ; 

int gpio_request(unsigned gpio, const char *label)
{
	if (gpio >= AR7_GPIO_MAX)
		return -EINVAL;

	if (ar7_gpio_list[gpio])
		return -EBUSY;

	if (label)
		ar7_gpio_list[gpio] = label;
	else
		ar7_gpio_list[gpio] = "busy";

	return 0;
}