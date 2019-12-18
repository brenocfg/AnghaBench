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
 size_t BLUE_BALANCE_IDX ; 
 int /*<<< orphan*/  D_V4L2 ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  PO1030_BLUE_GAIN ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int po1030_set_blue_balance(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	s32 *sensor_settings = sd->sensor_priv;
	u8 i2c_data;
	int err;

	sensor_settings[BLUE_BALANCE_IDX] = val;

	i2c_data = val & 0xff;
	PDEBUG(D_V4L2, "Set blue gain to %d", i2c_data);
	err = m5602_write_sensor(sd, PO1030_BLUE_GAIN,
				  &i2c_data, 1);

	return err;
}