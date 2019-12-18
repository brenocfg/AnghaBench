#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sd {int i2c_addr; int hstart; int vstart; int /*<<< orphan*/  sensor; } ;
struct gspca_dev {int ctrl_dis; } ;
struct TYPE_5__ {int reg; int val; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int AUTOGAIN_IDX ; 
 int ENODEV ; 
 int EXPOSURE_IDX ; 
 int GAIN_IDX ; 
 int /*<<< orphan*/  SENSOR_MT9V011 ; 
 int /*<<< orphan*/  SENSOR_MT9V111 ; 
 int /*<<< orphan*/  SENSOR_MT9V112 ; 
 int /*<<< orphan*/  err (char*) ; 
 int i2c_r2 (struct gspca_dev*,int,int*) ; 
 scalar_t__ i2c_w2 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  info (char*) ; 
 TYPE_1__* mt9v011_init ; 
 TYPE_1__* mt9v111_init ; 
 TYPE_1__* mt9v112_init ; 

__attribute__((used)) static int mt9v_init_sensor(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i;
	u16 value;
	int ret;

	sd->i2c_addr = 0x5d;
	ret = i2c_r2(gspca_dev, 0xff, &value);
	if ((ret == 0) && (value == 0x8243)) {
		for (i = 0; i < ARRAY_SIZE(mt9v011_init); i++) {
			if (i2c_w2(gspca_dev, mt9v011_init[i].reg,
					mt9v011_init[i].val) < 0) {
				err("MT9V011 sensor initialization failed");
				return -ENODEV;
			}
		}
		sd->hstart = 2;
		sd->vstart = 2;
		sd->sensor = SENSOR_MT9V011;
		info("MT9V011 sensor detected");
		return 0;
	}

	sd->i2c_addr = 0x5c;
	i2c_w2(gspca_dev, 0x01, 0x0004);
	ret = i2c_r2(gspca_dev, 0xff, &value);
	if ((ret == 0) && (value == 0x823a)) {
		for (i = 0; i < ARRAY_SIZE(mt9v111_init); i++) {
			if (i2c_w2(gspca_dev, mt9v111_init[i].reg,
					mt9v111_init[i].val) < 0) {
				err("MT9V111 sensor initialization failed");
				return -ENODEV;
			}
		}
		gspca_dev->ctrl_dis = (1 << EXPOSURE_IDX)
					| (1 << AUTOGAIN_IDX)
					| (1 << GAIN_IDX);
		sd->hstart = 2;
		sd->vstart = 2;
		sd->sensor = SENSOR_MT9V111;
		info("MT9V111 sensor detected");
		return 0;
	}

	sd->i2c_addr = 0x5d;
	ret = i2c_w2(gspca_dev, 0xf0, 0x0000);
	if (ret < 0) {
		sd->i2c_addr = 0x48;
		i2c_w2(gspca_dev, 0xf0, 0x0000);
	}
	ret = i2c_r2(gspca_dev, 0x00, &value);
	if ((ret == 0) && (value == 0x1229)) {
		for (i = 0; i < ARRAY_SIZE(mt9v112_init); i++) {
			if (i2c_w2(gspca_dev, mt9v112_init[i].reg,
					mt9v112_init[i].val) < 0) {
				err("MT9V112 sensor initialization failed");
				return -ENODEV;
			}
		}
		sd->hstart = 6;
		sd->vstart = 2;
		sd->sensor = SENSOR_MT9V112;
		info("MT9V112 sensor detected");
		return 0;
	}

	return -ENODEV;
}