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
 scalar_t__ GPIO_ISOUT (unsigned short) ; 
 scalar_t__ GPIO_ISRAM (unsigned short) ; 
 int /*<<< orphan*/  PIO_DRV_STATE ; 
 int /*<<< orphan*/  PIO_OUTP_CLR ; 
 int /*<<< orphan*/  PIO_OUTP_SET ; 
 int /*<<< orphan*/  PIO_SDOUTP_CLR ; 
 int /*<<< orphan*/  PIO_SDOUTP_SET ; 
 int /*<<< orphan*/  gpio_lock () ; 
 scalar_t__ gpio_read_bit (int /*<<< orphan*/ ,int) ; 
 int gpio_set_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_unlock () ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 

int pnx4008_gpio_write_pin(unsigned short pin, int output)
{
	int gpio = GPIO_BIT_MASK(pin);
	int ret = -EFAULT;

	gpio_lock();
	if (GPIO_ISOUT(pin)) {
		printk( "writing '%x' to '%x'\n",
				gpio, output ? PIO_OUTP_SET : PIO_OUTP_CLR );
		ret = gpio_set_bit(output ? PIO_OUTP_SET : PIO_OUTP_CLR, gpio);
	} else if (GPIO_ISRAM(pin)) {
		if (gpio_read_bit(PIO_DRV_STATE, gpio) > 0)
			ret = gpio_set_bit(output ? PIO_SDOUTP_SET :
					   PIO_SDOUTP_CLR, gpio);
	} else if (GPIO_ISBID(pin)) {
		if (gpio_read_bit(PIO_DRV_STATE, gpio) > 0)
			ret = gpio_set_bit(output ? PIO_OUTP_SET :
					   PIO_OUTP_CLR, gpio);
	}
	gpio_unlock();
	return ret;
}