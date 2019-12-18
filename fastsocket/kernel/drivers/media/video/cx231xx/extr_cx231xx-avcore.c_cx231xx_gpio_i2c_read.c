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
typedef  int u8 ;
struct cx231xx {int /*<<< orphan*/  gpio_i2c_lock; } ;

/* Variables and functions */
 int cx231xx_gpio_i2c_end (struct cx231xx*) ; 
 int cx231xx_gpio_i2c_read_ack (struct cx231xx*) ; 
 int cx231xx_gpio_i2c_read_byte (struct cx231xx*,int*) ; 
 int cx231xx_gpio_i2c_start (struct cx231xx*) ; 
 int cx231xx_gpio_i2c_write_ack (struct cx231xx*) ; 
 int cx231xx_gpio_i2c_write_byte (struct cx231xx*,int) ; 
 int cx231xx_gpio_i2c_write_nak (struct cx231xx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cx231xx_gpio_i2c_read(struct cx231xx *dev, u8 dev_addr, u8 *buf, u8 len)
{
	int status = 0;
	int i = 0;

	/* get the lock */
	mutex_lock(&dev->gpio_i2c_lock);

	/* start */
	status = cx231xx_gpio_i2c_start(dev);

	/* write dev_addr */
	status = cx231xx_gpio_i2c_write_byte(dev, (dev_addr << 1) + 1);

	/* readAck */
	status = cx231xx_gpio_i2c_read_ack(dev);

	/* read data */
	for (i = 0; i < len; i++) {
		/* read data */
		buf[i] = 0;
		status = cx231xx_gpio_i2c_read_byte(dev, &buf[i]);

		if ((i + 1) != len) {
			/* only do write ack if we more length */
			status = cx231xx_gpio_i2c_write_ack(dev);
		}
	}

	/* write NAK - inform reads are complete */
	status = cx231xx_gpio_i2c_write_nak(dev);

	/* write end */
	status = cx231xx_gpio_i2c_end(dev);

	/* release the lock */
	mutex_unlock(&dev->gpio_i2c_lock);

	return status;
}