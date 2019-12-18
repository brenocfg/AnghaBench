#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sd {int hstart; int vstart; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  err (char*,...) ; 
 scalar_t__ i2c_r2 (struct gspca_dev*,int,int*) ; 
 scalar_t__ i2c_w1 (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ov9650_init ; 

__attribute__((used)) static int ov9650_init_sensor(struct gspca_dev *gspca_dev)
{
	int i;
	u16 id;
	struct sd *sd = (struct sd *) gspca_dev;

	if (i2c_r2(gspca_dev, 0x1c, &id) < 0)
		return -EINVAL;

	if (id != 0x7fa2) {
		err("sensor id for ov9650 doesn't match (0x%04x)", id);
		return -ENODEV;
	}

	for (i = 0; i < ARRAY_SIZE(ov9650_init); i++) {
		if (i2c_w1(gspca_dev, ov9650_init[i].reg,
				ov9650_init[i].val) < 0) {
			err("OV9650 sensor initialization failed");
			return -ENODEV;
		}
	}
	sd->hstart = 1;
	sd->vstart = 7;
	return 0;
}