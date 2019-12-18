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
struct sensor_w_data {int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  flags; int /*<<< orphan*/  reg; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int sensor_write_reg (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sensor_write_regs(struct gspca_dev *gspca_dev,
	const struct sensor_w_data *data, int len)
{
	int i, rc;

	for (i = 0; i < len; i++) {
		rc = sensor_write_reg(gspca_dev, data[i].reg, data[i].flags,
					  data[i].data, data[i].len);
		if (rc < 0)
			return rc;
	}

	return 0;
}