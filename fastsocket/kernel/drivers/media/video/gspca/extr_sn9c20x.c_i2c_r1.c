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
struct sd {int i2c_addr; } ;
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ i2c_w (struct gspca_dev*,int*) ; 
 scalar_t__ reg_r (struct gspca_dev*,int,int) ; 

__attribute__((used)) static int i2c_r1(struct gspca_dev *gspca_dev, u8 reg, u8 *val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 row[8];

	row[0] = 0x81 | (1 << 4);
	row[1] = sd->i2c_addr;
	row[2] = reg;
	row[3] = 0;
	row[4] = 0;
	row[5] = 0;
	row[6] = 0;
	row[7] = 0x10;
	if (i2c_w(gspca_dev, row) < 0)
		return -EIO;
	row[0] = 0x81 | (1 << 4) | 0x02;
	row[2] = 0;
	if (i2c_w(gspca_dev, row) < 0)
		return -EIO;
	if (reg_r(gspca_dev, 0x10c2, 5) < 0)
		return -EIO;
	*val = gspca_dev->usb_buf[4];
	return 0;
}