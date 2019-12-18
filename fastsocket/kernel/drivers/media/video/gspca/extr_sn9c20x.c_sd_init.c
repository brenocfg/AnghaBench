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
struct sd {int i2c_addr; int flags; int sensor; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int ENODEV ; 
 int LED_REVERSE ; 
#define  SENSOR_HV7131R 137 
#define  SENSOR_MT9M001 136 
#define  SENSOR_MT9M111 135 
#define  SENSOR_MT9M112 134 
#define  SENSOR_MT9VPRB 133 
#define  SENSOR_OV7660 132 
#define  SENSOR_OV7670 131 
#define  SENSOR_OV9650 130 
#define  SENSOR_OV9655 129 
#define  SENSOR_SOI968 128 
 int** bridge_init ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  hv7131r_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  mt9m001_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  mt9m111_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  mt9m112_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  mt9v_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  ov7660_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  ov7670_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  ov9650_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  ov9655_init_sensor (struct gspca_dev*) ; 
 scalar_t__ reg_w (struct gspca_dev*,int,int*,int) ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  soi968_init_sensor (struct gspca_dev*) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i;
	u8 value;
	u8 i2c_init[9] =
		{0x80, sd->i2c_addr, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03};

	for (i = 0; i < ARRAY_SIZE(bridge_init); i++) {
		value = bridge_init[i][1];
		if (reg_w(gspca_dev, bridge_init[i][0], &value, 1) < 0) {
			err("Device initialization failed");
			return -ENODEV;
		}
	}

	if (sd->flags & LED_REVERSE)
		reg_w1(gspca_dev, 0x1006, 0x00);
	else
		reg_w1(gspca_dev, 0x1006, 0x20);

	if (reg_w(gspca_dev, 0x10c0, i2c_init, 9) < 0) {
		err("Device initialization failed");
		return -ENODEV;
	}

	switch (sd->sensor) {
	case SENSOR_OV9650:
		if (ov9650_init_sensor(gspca_dev) < 0)
			return -ENODEV;
		info("OV9650 sensor detected");
		break;
	case SENSOR_OV9655:
		if (ov9655_init_sensor(gspca_dev) < 0)
			return -ENODEV;
		info("OV9655 sensor detected");
		break;
	case SENSOR_SOI968:
		if (soi968_init_sensor(gspca_dev) < 0)
			return -ENODEV;
		info("SOI968 sensor detected");
		break;
	case SENSOR_OV7660:
		if (ov7660_init_sensor(gspca_dev) < 0)
			return -ENODEV;
		info("OV7660 sensor detected");
		break;
	case SENSOR_OV7670:
		if (ov7670_init_sensor(gspca_dev) < 0)
			return -ENODEV;
		info("OV7670 sensor detected");
		break;
	case SENSOR_MT9VPRB:
		if (mt9v_init_sensor(gspca_dev) < 0)
			return -ENODEV;
		break;
	case SENSOR_MT9M111:
		if (mt9m111_init_sensor(gspca_dev) < 0)
			return -ENODEV;
		info("MT9M111 sensor detected");
		break;
	case SENSOR_MT9M112:
		if (mt9m112_init_sensor(gspca_dev) < 0)
			return -ENODEV;
		info("MT9M112 sensor detected");
		break;
	case SENSOR_MT9M001:
		if (mt9m001_init_sensor(gspca_dev) < 0)
			return -ENODEV;
		break;
	case SENSOR_HV7131R:
		if (hv7131r_init_sensor(gspca_dev) < 0)
			return -ENODEV;
		info("HV7131R sensor detected");
		break;
	default:
		info("Unsupported Sensor");
		return -ENODEV;
	}

	return 0;
}