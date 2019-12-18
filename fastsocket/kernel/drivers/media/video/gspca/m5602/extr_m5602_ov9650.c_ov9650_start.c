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
struct sd {TYPE_2__ gspca_dev; scalar_t__* sensor_priv; } ;
typedef  scalar_t__ s32 ;
struct TYPE_3__ {int width; int height; int priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__**) ; 
 scalar_t__ BRIDGE ; 
 int /*<<< orphan*/  D_V4L2 ; 
 scalar_t__ M5602_XB_HSYNC_PARA ; 
 scalar_t__ M5602_XB_SIG_INI ; 
 scalar_t__ M5602_XB_VSYNC_PARA ; 
 int OV9650_CIF_SELECT ; 
 scalar_t__ OV9650_COM7 ; 
 int OV9650_LEFT_OFFSET ; 
 int OV9650_QCIF_SELECT ; 
 int OV9650_QVGA_SELECT ; 
 int OV9650_RAW_RGB_SELECT ; 
 int OV9650_RGB_SELECT ; 
 int OV9650_VGA_SELECT ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SENSOR ; 
 size_t VFLIP_IDX ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int m5602_write_bridge (struct sd*,scalar_t__,int) ; 
 int m5602_write_sensor (struct sd*,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  ov9650_flip_dmi_table ; 
 scalar_t__** res_init_ov9650 ; 

int ov9650_start(struct sd *sd)
{
	u8 data;
	int i, err = 0;
	struct cam *cam = &sd->gspca_dev.cam;
	s32 *sensor_settings = sd->sensor_priv;

	int width = cam->cam_mode[sd->gspca_dev.curr_mode].width;
	int height = cam->cam_mode[sd->gspca_dev.curr_mode].height;
	int ver_offs = cam->cam_mode[sd->gspca_dev.curr_mode].priv;
	int hor_offs = OV9650_LEFT_OFFSET;

	if ((!dmi_check_system(ov9650_flip_dmi_table) &&
		sensor_settings[VFLIP_IDX]) ||
		(dmi_check_system(ov9650_flip_dmi_table) &&
		!sensor_settings[VFLIP_IDX]))
		ver_offs--;

	if (width <= 320)
		hor_offs /= 2;

	/* Synthesize the vsync/hsync setup */
	for (i = 0; i < ARRAY_SIZE(res_init_ov9650) && !err; i++) {
		if (res_init_ov9650[i][0] == BRIDGE)
			err = m5602_write_bridge(sd, res_init_ov9650[i][1],
				res_init_ov9650[i][2]);
		else if (res_init_ov9650[i][0] == SENSOR) {
			data = res_init_ov9650[i][2];
			err = m5602_write_sensor(sd,
				res_init_ov9650[i][1], &data, 1);
		}
	}
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA,
				 ((ver_offs >> 8) & 0xff));
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA, (ver_offs & 0xff));
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_VSYNC_PARA, 0);
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

	err = m5602_write_bridge(sd, M5602_XB_HSYNC_PARA,
				 (hor_offs >> 8) & 0xff);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_HSYNC_PARA, hor_offs & 0xff);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_HSYNC_PARA,
				 ((width + hor_offs) >> 8) & 0xff);
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_HSYNC_PARA,
				 ((width + hor_offs) & 0xff));
	if (err < 0)
		return err;

	err = m5602_write_bridge(sd, M5602_XB_SIG_INI, 0);
	if (err < 0)
		return err;

	switch (width) {
	case 640:
		PDEBUG(D_V4L2, "Configuring camera for VGA mode");

		data = OV9650_VGA_SELECT | OV9650_RGB_SELECT |
		       OV9650_RAW_RGB_SELECT;
		err = m5602_write_sensor(sd, OV9650_COM7, &data, 1);
		break;

	case 352:
		PDEBUG(D_V4L2, "Configuring camera for CIF mode");

		data = OV9650_CIF_SELECT | OV9650_RGB_SELECT |
				OV9650_RAW_RGB_SELECT;
		err = m5602_write_sensor(sd, OV9650_COM7, &data, 1);
		break;

	case 320:
		PDEBUG(D_V4L2, "Configuring camera for QVGA mode");

		data = OV9650_QVGA_SELECT | OV9650_RGB_SELECT |
				OV9650_RAW_RGB_SELECT;
		err = m5602_write_sensor(sd, OV9650_COM7, &data, 1);
		break;

	case 176:
		PDEBUG(D_V4L2, "Configuring camera for QCIF mode");

		data = OV9650_QCIF_SELECT | OV9650_RGB_SELECT |
			OV9650_RAW_RGB_SELECT;
		err = m5602_write_sensor(sd, OV9650_COM7, &data, 1);
		break;
	}
	return err;
}