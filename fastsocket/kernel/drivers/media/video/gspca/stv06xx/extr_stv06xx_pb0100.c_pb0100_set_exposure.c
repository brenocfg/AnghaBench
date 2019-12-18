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
struct sd {scalar_t__* sensor_priv; } ;
struct gspca_dev {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ __s32 ;

/* Variables and functions */
 size_t AUTOGAIN_IDX ; 
 int /*<<< orphan*/  D_V4L2 ; 
 int EBUSY ; 
 size_t EXPOSURE_IDX ; 
 int /*<<< orphan*/  PB_RINTTIME ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pb0100_set_exposure(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	struct sd *sd = (struct sd *) gspca_dev;
	s32 *sensor_settings = sd->sensor_priv;

	if (sensor_settings[AUTOGAIN_IDX])
		return -EBUSY;

	sensor_settings[EXPOSURE_IDX] = val;
	err = stv06xx_write_sensor(sd, PB_RINTTIME, val);
	PDEBUG(D_V4L2, "Set exposure to %d, status: %d", val, err);

	return err;
}