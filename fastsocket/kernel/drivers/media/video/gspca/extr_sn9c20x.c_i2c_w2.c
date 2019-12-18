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
typedef  int u16 ;
struct sd {int i2c_addr; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int i2c_w (struct gspca_dev*,int*) ; 

__attribute__((used)) static int i2c_w2(struct gspca_dev *gspca_dev, u8 reg, u16 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 row[8];

	/*
	 * from the point of view of the bridge, the length
	 * includes the address
	 */
	row[0] = 0x81 | (3 << 4);
	row[1] = sd->i2c_addr;
	row[2] = reg;
	row[3] = (val >> 8) & 0xff;
	row[4] = val & 0xff;
	row[5] = 0x00;
	row[6] = 0x00;
	row[7] = 0x10;

	return i2c_w(gspca_dev, row);
}