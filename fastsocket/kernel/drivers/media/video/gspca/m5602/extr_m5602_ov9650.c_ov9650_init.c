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
typedef  scalar_t__ u8 ;
struct sd {int /*<<< orphan*/  gspca_dev; int /*<<< orphan*/ * sensor_priv; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__**) ; 
 size_t AUTO_EXPOSURE_IDX ; 
 size_t AUTO_GAIN_CTRL_IDX ; 
 size_t AUTO_WHITE_BALANCE_IDX ; 
 size_t BLUE_BALANCE_IDX ; 
 size_t EXPOSURE_IDX ; 
 size_t GAIN_IDX ; 
 size_t HFLIP_IDX ; 
 size_t RED_BALANCE_IDX ; 
 scalar_t__ SENSOR ; 
 size_t VFLIP_IDX ; 
 scalar_t__ dump_sensor ; 
 scalar_t__** init_ov9650 ; 
 int m5602_write_bridge (struct sd*,scalar_t__,scalar_t__) ; 
 int m5602_write_sensor (struct sd*,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  ov9650_dump_registers (struct sd*) ; 
 int ov9650_set_auto_exposure (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ov9650_set_auto_gain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ov9650_set_auto_white_balance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ov9650_set_blue_balance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ov9650_set_exposure (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ov9650_set_gain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ov9650_set_hflip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ov9650_set_red_balance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ov9650_set_vflip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ov9650_init(struct sd *sd)
{
	int i, err = 0;
	u8 data;
	s32 *sensor_settings = sd->sensor_priv;

	if (dump_sensor)
		ov9650_dump_registers(sd);

	for (i = 0; i < ARRAY_SIZE(init_ov9650) && !err; i++) {
		data = init_ov9650[i][2];
		if (init_ov9650[i][0] == SENSOR)
			err = m5602_write_sensor(sd, init_ov9650[i][1],
						  &data, 1);
		else
			err = m5602_write_bridge(sd, init_ov9650[i][1], data);
	}

	err = ov9650_set_exposure(&sd->gspca_dev,
				   sensor_settings[EXPOSURE_IDX]);
	if (err < 0)
		return err;

	err = ov9650_set_gain(&sd->gspca_dev, sensor_settings[GAIN_IDX]);
	if (err < 0)
		return err;

	err = ov9650_set_red_balance(&sd->gspca_dev,
				      sensor_settings[RED_BALANCE_IDX]);
	if (err < 0)
		return err;

	err = ov9650_set_blue_balance(&sd->gspca_dev,
				       sensor_settings[BLUE_BALANCE_IDX]);
	if (err < 0)
		return err;

	err = ov9650_set_hflip(&sd->gspca_dev, sensor_settings[HFLIP_IDX]);
	if (err < 0)
		return err;

	err = ov9650_set_vflip(&sd->gspca_dev, sensor_settings[VFLIP_IDX]);
	if (err < 0)
		return err;

	err = ov9650_set_auto_exposure(&sd->gspca_dev,
				sensor_settings[AUTO_EXPOSURE_IDX]);
	if (err < 0)
		return err;

	err = ov9650_set_auto_white_balance(&sd->gspca_dev,
				sensor_settings[AUTO_WHITE_BALANCE_IDX]);
	if (err < 0)
		return err;

	err = ov9650_set_auto_gain(&sd->gspca_dev,
				sensor_settings[AUTO_GAIN_CTRL_IDX]);
	return err;
}