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
 scalar_t__ GPIO_ISMUX (unsigned short) ; 
 scalar_t__ GPIO_ISOUT (unsigned short) ; 
 int /*<<< orphan*/  PIO_MUX_STATE ; 
 int /*<<< orphan*/  gpio_lock () ; 
 int gpio_read_bit (int /*<<< orphan*/ ,int) ; 
 int* gpio_to_mux_map ; 
 int /*<<< orphan*/  gpio_unlock () ; 
 int* outp_to_mux_map ; 

int pnx4008_gpio_read_pin_mux(unsigned short pin)
{
	int gpio = GPIO_BIT_MASK(pin);
	int ret = -EFAULT;

	gpio_lock();
	if (GPIO_ISBID(pin)) {
		ret = gpio_read_bit(PIO_MUX_STATE, gpio_to_mux_map[gpio]);
	} else if (GPIO_ISOUT(pin)) {
		ret = gpio_read_bit(PIO_MUX_STATE, outp_to_mux_map[gpio]);
	} else if (GPIO_ISMUX(pin)) {
		ret = gpio_read_bit(PIO_MUX_STATE, gpio);
	}
	gpio_unlock();
	return ret;
}