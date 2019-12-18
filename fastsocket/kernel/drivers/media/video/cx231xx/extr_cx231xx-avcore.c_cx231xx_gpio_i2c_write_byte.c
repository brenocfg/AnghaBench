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
typedef  int u8 ;
struct TYPE_2__ {int tuner_scl_gpio; int tuner_sda_gpio; } ;
struct cx231xx {int gpio_dir; int gpio_val; TYPE_1__ board; } ;

/* Variables and functions */
 int cx231xx_set_gpio_bit (struct cx231xx*,int,int*) ; 

int cx231xx_gpio_i2c_write_byte(struct cx231xx *dev, u8 data)
{
	int status = 0;
	u8 i;

	/* set SCL to output ; set SDA to output */
	dev->gpio_dir |= 1 << dev->board.tuner_scl_gpio;
	dev->gpio_dir |= 1 << dev->board.tuner_sda_gpio;

	for (i = 0; i < 8; i++) {
		if (((data << i) & 0x80) == 0) {
			/* set SCL to output 0; set SDA to output 0     */
			dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
			dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      (u8 *)&dev->gpio_val);

			/* set SCL to output 1; set SDA to output 0     */
			dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      (u8 *)&dev->gpio_val);

			/* set SCL to output 0; set SDA to output 0     */
			dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      (u8 *)&dev->gpio_val);
		} else {
			/* set SCL to output 0; set SDA to output 1     */
			dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
			dev->gpio_val |= 1 << dev->board.tuner_sda_gpio;
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      (u8 *)&dev->gpio_val);

			/* set SCL to output 1; set SDA to output 1     */
			dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      (u8 *)&dev->gpio_val);

			/* set SCL to output 0; set SDA to output 1     */
			dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      (u8 *)&dev->gpio_val);
		}
	}
	return status;
}