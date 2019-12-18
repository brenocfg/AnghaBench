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
struct sd {int hstart; int vstart; } ;
struct gspca_dev {int ctrl_dis; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENODEV ; 
 int HFLIP_IDX ; 
 int VFLIP_IDX ; 
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ i2c_w1 (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ov9655_init ; 

__attribute__((used)) static int ov9655_init_sensor(struct gspca_dev *gspca_dev)
{
	int i;
	struct sd *sd = (struct sd *) gspca_dev;

	for (i = 0; i < ARRAY_SIZE(ov9655_init); i++) {
		if (i2c_w1(gspca_dev, ov9655_init[i].reg,
				ov9655_init[i].val) < 0) {
			err("OV9655 sensor initialization failed");
			return -ENODEV;
		}
	}
	/* disable hflip and vflip */
	gspca_dev->ctrl_dis = (1 << HFLIP_IDX) | (1 << VFLIP_IDX);
	sd->hstart = 1;
	sd->vstart = 2;
	return 0;
}