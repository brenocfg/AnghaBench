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
typedef  int u8 ;
struct sd {int* sensor_priv; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_V4L2 ; 
 size_t HFLIP_IDX ; 
 int /*<<< orphan*/  OV9650_MVFP ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 size_t VFLIP_IDX ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ov9650_flip_dmi_table ; 

__attribute__((used)) static int ov9650_set_hflip(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	u8 i2c_data;
	struct sd *sd = (struct sd *) gspca_dev;
	s32 *sensor_settings = sd->sensor_priv;

	PDEBUG(D_V4L2, "Set horizontal flip to %d", val);

	sensor_settings[HFLIP_IDX] = val;

	if (!dmi_check_system(ov9650_flip_dmi_table))
		i2c_data = ((val & 0x01) << 5) |
				(sensor_settings[VFLIP_IDX] << 4);
	else
		i2c_data = ((val & 0x01) << 5) |
				(!sensor_settings[VFLIP_IDX] << 4);

	err = m5602_write_sensor(sd, OV9650_MVFP, &i2c_data, 1);

	return err;
}