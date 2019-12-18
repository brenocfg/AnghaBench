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
 size_t NOISE_SUPP_IDX ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  S5K4AA_NOISE_SUPP ; 
 int /*<<< orphan*/  S5K4AA_PAGE_MAP ; 
 int S5K4AA_PAGE_MAP_2 ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int s5k4aa_set_noise(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	s32 *sensor_settings = sd->sensor_priv;
	u8 data = S5K4AA_PAGE_MAP_2;
	int err;

	sensor_settings[NOISE_SUPP_IDX] = val;

	PDEBUG(D_V4L2, "Set noise to %d", val);
	err = m5602_write_sensor(sd, S5K4AA_PAGE_MAP, &data, 1);
	if (err < 0)
		return err;

	data = val & 0x01;
	return m5602_write_sensor(sd, S5K4AA_NOISE_SUPP, &data, 1);
}