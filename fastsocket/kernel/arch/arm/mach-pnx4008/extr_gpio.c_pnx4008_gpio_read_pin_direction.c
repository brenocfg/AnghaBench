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
 int EFAULT ; 
 int GPIO_BIT_MASK (unsigned short) ; 
 scalar_t__ GPIO_ISBID (unsigned short) ; 
 scalar_t__ GPIO_ISRAM (unsigned short) ; 
 int /*<<< orphan*/  PIO_DRV_STATE ; 
 int /*<<< orphan*/  gpio_lock () ; 
 int gpio_read_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_unlock () ; 

int pnx4008_gpio_read_pin_direction(unsigned short pin)
{
	int gpio = GPIO_BIT_MASK(pin);
	int ret = -EFAULT;

	gpio_lock();
	if (GPIO_ISBID(pin) || GPIO_ISRAM(pin)) {
		ret = gpio_read_bit(PIO_DRV_STATE, gpio);
	}
	gpio_unlock();
	return ret;
}