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
struct sd {int sensor; int i2c_addr; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
#define  SENSOR_ADCM1700 130 
#define  SENSOR_GC0307 129 
#define  SENSOR_OM6802 128 
 int /*<<< orphan*/  i2c_w8 (struct gspca_dev*,int*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void i2c_r(struct gspca_dev *gspca_dev, u8 reg, int len)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 mode[8];

	switch (sd->sensor) {
	case SENSOR_ADCM1700:
	case SENSOR_OM6802:
	case SENSOR_GC0307:		/* i2c command = a0 (100 kHz) */
		mode[0] = 0x80 | 0x10;
		break;
	default:			/* i2c command = 91 (400 kHz) */
		mode[0] = 0x81 | 0x10;
		break;
	}
	mode[1] = sd->i2c_addr;
	mode[2] = reg;
	mode[3] = 0;
	mode[4] = 0;
	mode[5] = 0;
	mode[6] = 0;
	mode[7] = 0x10;
	i2c_w8(gspca_dev, mode);
	msleep(2);
	mode[0] = (mode[0] & 0x81) | (len << 4) | 0x02;
	mode[2] = 0;
	i2c_w8(gspca_dev, mode);
	msleep(2);
	reg_r(gspca_dev, 0x0a, 5);
}