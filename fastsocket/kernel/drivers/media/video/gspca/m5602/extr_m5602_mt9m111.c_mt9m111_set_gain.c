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
 int EINVAL ; 
 size_t GAIN_IDX ; 
 int INITIAL_MAX_GAIN ; 
 int /*<<< orphan*/  MT9M111_PAGE_MAP ; 
 int /*<<< orphan*/  MT9M111_SC_GLOBAL_GAIN ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int mt9m111_set_gain(struct gspca_dev *gspca_dev, __s32 val)
{
	int err, tmp;
	u8 data[2] = {0x00, 0x00};
	struct sd *sd = (struct sd *) gspca_dev;
	s32 *sensor_settings = sd->sensor_priv;

	sensor_settings[GAIN_IDX] = val;

	/* Set the correct page map */
	err = m5602_write_sensor(sd, MT9M111_PAGE_MAP, data, 2);
	if (err < 0)
		return err;

	if (val >= INITIAL_MAX_GAIN * 2 * 2 * 2)
		return -EINVAL;

	if ((val >= INITIAL_MAX_GAIN * 2 * 2) &&
	    (val < (INITIAL_MAX_GAIN - 1) * 2 * 2 * 2))
		tmp = (1 << 10) | (val << 9) |
				(val << 8) | (val / 8);
	else if ((val >= INITIAL_MAX_GAIN * 2) &&
		 (val <  INITIAL_MAX_GAIN * 2 * 2))
		tmp = (1 << 9) | (1 << 8) | (val / 4);
	else if ((val >= INITIAL_MAX_GAIN) &&
		 (val < INITIAL_MAX_GAIN * 2))
		tmp = (1 << 8) | (val / 2);
	else
		tmp = val;

	data[1] = (tmp & 0xff);
	data[0] = (tmp & 0xff00) >> 8;
	PDEBUG(D_V4L2, "tmp=%d, data[1]=%d, data[0]=%d", tmp,
	       data[1], data[0]);

	err = m5602_write_sensor(sd, MT9M111_SC_GLOBAL_GAIN,
				   data, 2);

	return err;
}