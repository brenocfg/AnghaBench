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
 unsigned long EFAULT ; 
 int GPIO_BIT_MASK (unsigned short) ; 
 scalar_t__ GPIO_ISBID (unsigned short) ; 
 scalar_t__ GPIO_ISIN (unsigned short) ; 
 scalar_t__ GPIO_ISOUT (unsigned short) ; 
 scalar_t__ GPIO_ISRAM (unsigned short) ; 
 int /*<<< orphan*/  PIO_DRV_STATE ; 
 int /*<<< orphan*/  PIO_INP_STATE ; 
 int /*<<< orphan*/  PIO_OUTP_STATE ; 
 int /*<<< orphan*/  PIO_SDINP_STATE ; 
 int /*<<< orphan*/  gpio_lock () ; 
 unsigned long gpio_read_bit (int /*<<< orphan*/ ,int) ; 
 int* gpio_to_inp_map ; 
 int /*<<< orphan*/  gpio_unlock () ; 

unsigned long pnx4008_gpio_read_pin(unsigned short pin)
{
	unsigned long ret = -EFAULT;
	int gpio = GPIO_BIT_MASK(pin);
	gpio_lock();
	if (GPIO_ISOUT(pin)) {
		ret = gpio_read_bit(PIO_OUTP_STATE, gpio);
	} else if (GPIO_ISRAM(pin)) {
		if (gpio_read_bit(PIO_DRV_STATE, gpio) == 0) {
			ret = gpio_read_bit(PIO_SDINP_STATE, gpio);
		}
	} else if (GPIO_ISBID(pin)) {
		ret = gpio_read_bit(PIO_DRV_STATE, gpio);
		if (ret > 0)
			ret = gpio_read_bit(PIO_OUTP_STATE, gpio);
		else if (ret == 0)
			ret =
			    gpio_read_bit(PIO_INP_STATE, gpio_to_inp_map[gpio]);
	} else if (GPIO_ISIN(pin)) {
		ret = gpio_read_bit(PIO_INP_STATE, gpio);
	}
	gpio_unlock();
	return ret;
}