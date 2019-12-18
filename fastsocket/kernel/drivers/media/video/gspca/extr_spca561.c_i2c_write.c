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
struct gspca_dev {int /*<<< orphan*/ * usb_buf; int /*<<< orphan*/  dev; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w_val (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void i2c_write(struct gspca_dev *gspca_dev, __u16 value, __u16 reg)
{
	int retry = 60;

	reg_w_val(gspca_dev->dev, 0x8801, reg);
	reg_w_val(gspca_dev->dev, 0x8805, value);
	reg_w_val(gspca_dev->dev, 0x8800, value >> 8);
	do {
		reg_r(gspca_dev, 0x8803, 1);
		if (!gspca_dev->usb_buf[0])
			return;
		msleep(10);
	} while (--retry);
}