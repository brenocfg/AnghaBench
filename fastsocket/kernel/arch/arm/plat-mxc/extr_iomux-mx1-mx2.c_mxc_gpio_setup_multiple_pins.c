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
 int EINVAL ; 
 int const GPIO_PIN_MASK ; 
 int const GPIO_PORT_MASK ; 
 int GPIO_PORT_MAX ; 
 int gpio_request (unsigned int,char const*) ; 
 int /*<<< orphan*/  mxc_gpio_mode (unsigned int) ; 
 int /*<<< orphan*/  mxc_gpio_release_multiple_pins (int const*,int) ; 

int mxc_gpio_setup_multiple_pins(const int *pin_list, unsigned count,
		const char *label)
{
	const int *p = pin_list;
	int i;
	unsigned gpio;
	unsigned mode;
	int ret = -EINVAL;

	for (i = 0; i < count; i++) {
		gpio = *p & (GPIO_PIN_MASK | GPIO_PORT_MASK);
		mode = *p & ~(GPIO_PIN_MASK | GPIO_PORT_MASK);

		if (gpio >= (GPIO_PORT_MAX + 1) * 32)
			goto setup_error;

		ret = gpio_request(gpio, label);
		if (ret)
			goto setup_error;

		mxc_gpio_mode(gpio | mode);

		p++;
	}
	return 0;

setup_error:
	mxc_gpio_release_multiple_pins(pin_list, i);
	return ret;
}