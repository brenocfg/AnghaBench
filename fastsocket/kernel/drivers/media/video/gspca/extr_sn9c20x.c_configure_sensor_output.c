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
struct sd {int sensor; int hstart; int vstart; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int MODE_SXGA ; 
#define  SENSOR_MT9M111 131 
#define  SENSOR_MT9M112 130 
#define  SENSOR_OV9650 129 
#define  SENSOR_SOI968 128 
 int /*<<< orphan*/  i2c_r1 (struct gspca_dev*,int,int*) ; 
 int /*<<< orphan*/  i2c_w1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  i2c_w2 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void configure_sensor_output(struct gspca_dev *gspca_dev, int mode)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 value;
	switch (sd->sensor) {
	case SENSOR_SOI968:
		if (mode & MODE_SXGA) {
			i2c_w1(gspca_dev, 0x17, 0x1d);
			i2c_w1(gspca_dev, 0x18, 0xbd);
			i2c_w1(gspca_dev, 0x19, 0x01);
			i2c_w1(gspca_dev, 0x1a, 0x81);
			i2c_w1(gspca_dev, 0x12, 0x00);
			sd->hstart = 140;
			sd->vstart = 19;
		} else {
			i2c_w1(gspca_dev, 0x17, 0x13);
			i2c_w1(gspca_dev, 0x18, 0x63);
			i2c_w1(gspca_dev, 0x19, 0x01);
			i2c_w1(gspca_dev, 0x1a, 0x79);
			i2c_w1(gspca_dev, 0x12, 0x40);
			sd->hstart = 60;
			sd->vstart = 11;
		}
		break;
	case SENSOR_OV9650:
		if (mode & MODE_SXGA) {
			i2c_w1(gspca_dev, 0x17, 0x1b);
			i2c_w1(gspca_dev, 0x18, 0xbc);
			i2c_w1(gspca_dev, 0x19, 0x01);
			i2c_w1(gspca_dev, 0x1a, 0x82);
			i2c_r1(gspca_dev, 0x12, &value);
			i2c_w1(gspca_dev, 0x12, value & 0x07);
		} else {
			i2c_w1(gspca_dev, 0x17, 0x24);
			i2c_w1(gspca_dev, 0x18, 0xc5);
			i2c_w1(gspca_dev, 0x19, 0x00);
			i2c_w1(gspca_dev, 0x1a, 0x3c);
			i2c_r1(gspca_dev, 0x12, &value);
			i2c_w1(gspca_dev, 0x12, (value & 0x7) | 0x40);
		}
		break;
	case SENSOR_MT9M112:
	case SENSOR_MT9M111:
		if (mode & MODE_SXGA) {
			i2c_w2(gspca_dev, 0xf0, 0x0002);
			i2c_w2(gspca_dev, 0xc8, 0x970b);
			i2c_w2(gspca_dev, 0xf0, 0x0000);
		} else {
			i2c_w2(gspca_dev, 0xf0, 0x0002);
			i2c_w2(gspca_dev, 0xc8, 0x8000);
			i2c_w2(gspca_dev, 0xf0, 0x0000);
		}
		break;
	}
}