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
 int /*<<< orphan*/  D_V4L2 ; 
 size_t EXPOSURE_IDX ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int VV6410_CIF_LINELENGTH ; 
 int /*<<< orphan*/  VV6410_COARSEH ; 
 int /*<<< orphan*/  VV6410_COARSEL ; 
 int /*<<< orphan*/  VV6410_FINEH ; 
 int /*<<< orphan*/  VV6410_FINEL ; 
 unsigned int min (int,int) ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int vv6410_set_exposure(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	struct sd *sd = (struct sd *) gspca_dev;
	s32 *sensor_settings = sd->sensor_priv;
	unsigned int fine, coarse;

	sensor_settings[EXPOSURE_IDX] = val;

	val = (val * val >> 14) + val / 4;

	fine = val % VV6410_CIF_LINELENGTH;
	coarse = min(512, val / VV6410_CIF_LINELENGTH);

	PDEBUG(D_V4L2, "Set coarse exposure to %d, fine expsure to %d",
	       coarse, fine);

	err = stv06xx_write_sensor(sd, VV6410_FINEH, fine >> 8);
	if (err < 0)
		goto out;

	err = stv06xx_write_sensor(sd, VV6410_FINEL, fine & 0xff);
	if (err < 0)
		goto out;

	err = stv06xx_write_sensor(sd, VV6410_COARSEH, coarse >> 8);
	if (err < 0)
		goto out;

	err = stv06xx_write_sensor(sd, VV6410_COARSEL, coarse & 0xff);

out:
	return err;
}