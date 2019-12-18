#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cam {TYPE_1__* cam_mode; } ;
struct TYPE_4__ {size_t curr_mode; struct cam cam; } ;
struct sd {int* sensor_priv; TYPE_2__ gspca_dev; } ;
typedef  int s32 ;
struct TYPE_3__ {int width; int height; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__**) ; 
 scalar_t__ BRIDGE ; 
 int /*<<< orphan*/  D_V4L2 ; 
 size_t HFLIP_IDX ; 
 scalar_t__ M5602_XB_HSYNC_PARA ; 
 scalar_t__ M5602_XB_SIG_INI ; 
 scalar_t__ M5602_XB_VSYNC_PARA ; 
 int MT9M111_RMB_COLUMN_SKIP_2X ; 
 int MT9M111_RMB_COLUMN_SKIP_4X ; 
 int MT9M111_RMB_OVER_SIZED ; 
 int MT9M111_RMB_ROW_SKIP_2X ; 
 int MT9M111_RMB_ROW_SKIP_4X ; 
 scalar_t__ MT9M111_SC_R_MODE_CONTEXT_B ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 size_t VFLIP_IDX ; 
 int m5602_write_bridge (struct sd*,scalar_t__,int) ; 
 int m5602_write_sensor (struct sd*,scalar_t__,int*,int) ; 
 scalar_t__** start_mt9m111 ; 

int mt9m111_start(struct sd *sd)
{
	int i, err = 0;
	u8 data[2];
	struct cam *cam = &sd->gspca_dev.cam;
	s32 *sensor_settings = sd->sensor_priv;

	int width = cam->cam_mode[sd->gspca_dev.curr_mode].width - 1;
	int height = cam->cam_mode[sd->gspca_dev.curr_mode].height;

	for (i = 0; i < ARRAY_SIZE(start_mt9m111) && !err; i++) {
		if (start_mt9m111[i][0] == BRIDGE) {
			err = m5602_write_bridge(sd,
				start_mt9m111[i][1],
				start_mt9m111[i][2]);
		} else {
			data[0] = start_mt9m111[i][2];
			data[1] = start_mt9m111[i][3];
			err = m5602_write_sensor(sd,
				start_mt9m111[i][1], data, 2);
		}
	}
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA, (height >> 8) & 0xff);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA, (height & 0xff));
	if (err < 0)
		return err;

	for (i = 0; i < 2 && !err; i++)
		err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA, 0);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_SIG_INI, 0);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_SIG_INI, 2);
	if (err < 0)
		return err;

	for (i = 0; i < 2 && !err; i++)
		err = m5602_write_bridge(sd, M5602_XB_HSYNC_PARA, 0);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_HSYNC_PARA,
				 (width >> 8) & 0xff);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_HSYNC_PARA, width & 0xff);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_SIG_INI, 0);
	if (err < 0)
		return err;

	switch (width) {
	case 640:
		PDEBUG(D_V4L2, "Configuring camera for VGA mode");
		data[0] = MT9M111_RMB_OVER_SIZED;
		data[1] = MT9M111_RMB_ROW_SKIP_2X |
			  MT9M111_RMB_COLUMN_SKIP_2X |
			  (sensor_settings[VFLIP_IDX] << 0) |
			  (sensor_settings[HFLIP_IDX] << 1);

		err = m5602_write_sensor(sd,
					 MT9M111_SC_R_MODE_CONTEXT_B, data, 2);
		break;

	case 320:
		PDEBUG(D_V4L2, "Configuring camera for QVGA mode");
		data[0] = MT9M111_RMB_OVER_SIZED;
		data[1] = MT9M111_RMB_ROW_SKIP_4X |
				MT9M111_RMB_COLUMN_SKIP_4X |
				(sensor_settings[VFLIP_IDX] << 0) |
				(sensor_settings[HFLIP_IDX] << 1);
		err = m5602_write_sensor(sd,
					 MT9M111_SC_R_MODE_CONTEXT_B, data, 2);
		break;
	}
	return err;
}