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
struct sd {int i2c_addr; int sensor; int exposure; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
#define  SENSOR_HV7131R 135 
#define  SENSOR_MT9M001 134 
#define  SENSOR_MT9V011 133 
#define  SENSOR_MT9V112 132 
#define  SENSOR_OV7660 131 
#define  SENSOR_OV7670 130 
#define  SENSOR_OV9650 129 
#define  SENSOR_OV9655 128 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int*) ; 

__attribute__((used)) static int set_exposure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 exp[8] = {0x81, sd->i2c_addr, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e};
	switch (sd->sensor) {
	case SENSOR_OV7660:
	case SENSOR_OV7670:
	case SENSOR_OV9655:
	case SENSOR_OV9650:
		exp[0] |= (3 << 4);
		exp[2] = 0x2d;
		exp[3] = sd->exposure & 0xff;
		exp[4] = sd->exposure >> 8;
		break;
	case SENSOR_MT9M001:
	case SENSOR_MT9V112:
	case SENSOR_MT9V011:
		exp[0] |= (3 << 4);
		exp[2] = 0x09;
		exp[3] = sd->exposure >> 8;
		exp[4] = sd->exposure & 0xff;
		break;
	case SENSOR_HV7131R:
		exp[0] |= (4 << 4);
		exp[2] = 0x25;
		exp[3] = (sd->exposure >> 5) & 0xff;
		exp[4] = (sd->exposure << 3) & 0xff;
		exp[5] = 0;
		break;
	default:
		return 0;
	}
	i2c_w(gspca_dev, exp);
	return 0;
}