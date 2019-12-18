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
struct sd {int vstart; scalar_t__ hstart; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  err (char*) ; 
 TYPE_1__* hv7131r_init ; 
 scalar_t__ i2c_w1 (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hv7131r_init_sensor(struct gspca_dev *gspca_dev)
{
	int i;
	struct sd *sd = (struct sd *) gspca_dev;

	for (i = 0; i < ARRAY_SIZE(hv7131r_init); i++) {
		if (i2c_w1(gspca_dev, hv7131r_init[i].reg,
				hv7131r_init[i].val) < 0) {
			err("HV7131R Sensor initialization failed");
			return -ENODEV;
		}
	}
	sd->hstart = 0;
	sd->vstart = 1;
	return 0;
}