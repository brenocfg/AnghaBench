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
typedef  void* u32 ;
struct TYPE_2__ {int tuner_sda_gpio; int tuner_scl_gpio; } ;
struct cx231xx {int gpio_dir; int gpio_val; TYPE_1__ board; } ;

/* Variables and functions */
 int cx231xx_get_gpio_bit (struct cx231xx*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx231xx_info (char*,int) ; 
 int cx231xx_set_gpio_bit (struct cx231xx*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

int cx231xx_gpio_i2c_read_ack(struct cx231xx *dev)
{
	int status = 0;
	u32 gpio_logic_value = 0;
	int nCnt = 10;
	int nInit = nCnt;

	/* clock stretch; set SCL to input; set SDA to input;
	   get SCL value till SCL = 1 */
	dev->gpio_dir &= ~(1 << dev->board.tuner_sda_gpio);
	dev->gpio_dir &= ~(1 << dev->board.tuner_scl_gpio);

	gpio_logic_value = dev->gpio_val;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, (u8 *)&dev->gpio_val);

	do {
		msleep(2);
		status = cx231xx_get_gpio_bit(dev, dev->gpio_dir,
					      (u8 *)&dev->gpio_val);
		nCnt--;
	} while (((dev->gpio_val &
			  (1 << dev->board.tuner_scl_gpio)) == 0) &&
			 (nCnt > 0));

	if (nCnt == 0)
		cx231xx_info("No ACK after %d msec -GPIO I2C failed!",
			     nInit * 10);

	/*
	 * readAck
	 * through clock stretch, slave has given a SCL signal,
	 * so the SDA data can be directly read.
	 */
	status = cx231xx_get_gpio_bit(dev, dev->gpio_dir, (u8 *)&dev->gpio_val);

	if ((dev->gpio_val & 1 << dev->board.tuner_sda_gpio) == 0) {
		dev->gpio_val = gpio_logic_value;
		dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);
		status = 0;
	} else {
		dev->gpio_val = gpio_logic_value;
		dev->gpio_val |= (1 << dev->board.tuner_sda_gpio);
	}

	/* read SDA end, set the SCL to output 0, after this operation,
	   SDA direction can be changed. */
	dev->gpio_val = gpio_logic_value;
	dev->gpio_dir |= (1 << dev->board.tuner_scl_gpio);
	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, (u8 *)&dev->gpio_val);

	return status;
}