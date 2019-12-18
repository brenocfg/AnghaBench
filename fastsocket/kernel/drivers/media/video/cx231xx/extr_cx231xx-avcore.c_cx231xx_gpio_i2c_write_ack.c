#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int tuner_sda_gpio; int tuner_scl_gpio; } ;
struct cx231xx {int gpio_dir; int gpio_val; TYPE_1__ board; } ;

/* Variables and functions */
 int cx231xx_set_gpio_bit (struct cx231xx*,int,int /*<<< orphan*/ *) ; 

int cx231xx_gpio_i2c_write_ack(struct cx231xx *dev)
{
	int status = 0;

	/* set SDA to ouput */
	dev->gpio_dir |= 1 << dev->board.tuner_sda_gpio;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, (u8 *)&dev->gpio_val);

	/* set SCL = 0 (output); set SDA = 0 (output) */
	dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);
	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, (u8 *)&dev->gpio_val);

	/* set SCL = 1 (output); set SDA = 0 (output) */
	dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, (u8 *)&dev->gpio_val);

	/* set SCL = 0 (output); set SDA = 0 (output) */
	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, (u8 *)&dev->gpio_val);

	/* set SDA to input,and then the slave will read data from SDA. */
	dev->gpio_dir &= ~(1 << dev->board.tuner_sda_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, (u8 *)&dev->gpio_val);

	return status;
}