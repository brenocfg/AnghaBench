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
struct sd {int* sensor_priv; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;
typedef  int __s32 ;

/* Variables and functions */
 size_t AUTOGAIN_IDX ; 
 int BIT (int) ; 
 int /*<<< orphan*/  D_V4L2 ; 
 size_t NATURAL_IDX ; 
 int /*<<< orphan*/  PB_EXPGAIN ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pb0100_set_autogain(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	struct sd *sd = (struct sd *) gspca_dev;
	s32 *sensor_settings = sd->sensor_priv;

	sensor_settings[AUTOGAIN_IDX] = val;
	if (sensor_settings[AUTOGAIN_IDX]) {
		if (sensor_settings[NATURAL_IDX])
			val = BIT(6)|BIT(4)|BIT(0);
		else
			val = BIT(4)|BIT(0);
	} else
		val = 0;

	err = stv06xx_write_sensor(sd, PB_EXPGAIN, val);
	PDEBUG(D_V4L2, "Set autogain to %d (natural: %d), status: %d",
	       sensor_settings[AUTOGAIN_IDX], sensor_settings[NATURAL_IDX],
	       err);

	return err;
}