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
 int /*<<< orphan*/  D_V4L2 ; 
 int EBUSY ; 
 size_t GAIN_IDX ; 
 int /*<<< orphan*/  PB_RGAIN ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int) ; 
 size_t RED_BALANCE_IDX ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pb0100_set_red_balance(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	struct sd *sd = (struct sd *) gspca_dev;
	s32 *sensor_settings = sd->sensor_priv;

	if (sensor_settings[AUTOGAIN_IDX])
		return -EBUSY;

	sensor_settings[RED_BALANCE_IDX] = val;
	val += sensor_settings[GAIN_IDX];
	if (val < 0)
		val = 0;
	else if (val > 255)
		val = 255;

	err = stv06xx_write_sensor(sd, PB_RGAIN, val);
	PDEBUG(D_V4L2, "Set red gain to %d, status: %d", val, err);

	return err;
}