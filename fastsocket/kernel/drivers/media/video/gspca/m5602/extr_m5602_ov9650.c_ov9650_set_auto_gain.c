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
 size_t AUTO_GAIN_CTRL_IDX ; 
 int /*<<< orphan*/  D_V4L2 ; 
 int /*<<< orphan*/  OV9650_COM8 ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int m5602_read_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ov9650_set_auto_gain(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	u8 i2c_data;
	struct sd *sd = (struct sd *) gspca_dev;
	s32 *sensor_settings = sd->sensor_priv;

	PDEBUG(D_V4L2, "Set auto gain control to %d", val);

	sensor_settings[AUTO_GAIN_CTRL_IDX] = val;
	err = m5602_read_sensor(sd, OV9650_COM8, &i2c_data, 1);
	if (err < 0)
		return err;

	i2c_data = ((i2c_data & 0xfb) | ((val & 0x01) << 2));

	return m5602_write_sensor(sd, OV9650_COM8, &i2c_data, 1);
}