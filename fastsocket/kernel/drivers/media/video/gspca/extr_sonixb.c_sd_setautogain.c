#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd {size_t sensor; int /*<<< orphan*/  autogain_ignore_frames; int /*<<< orphan*/  gain; int /*<<< orphan*/  exposure; scalar_t__ autogain; scalar_t__ exp_too_low_cnt; scalar_t__ exp_too_high_cnt; } ;
struct gspca_dev {scalar_t__ streaming; } ;
typedef  scalar_t__ __s32 ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOGAIN_IGNORE_FRAMES ; 
 int /*<<< orphan*/  EXPOSURE_DEF ; 
 int F_COARSE_EXPO ; 
 int /*<<< orphan*/  GAIN_DEF ; 
 TYPE_1__* sensor_data ; 
 int /*<<< orphan*/  setexposure (struct gspca_dev*) ; 
 int /*<<< orphan*/  setgain (struct gspca_dev*) ; 

__attribute__((used)) static int sd_setautogain(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->autogain = val;
	sd->exp_too_high_cnt = 0;
	sd->exp_too_low_cnt = 0;

	/* when switching to autogain set defaults to make sure
	   we are on a valid point of the autogain gain /
	   exposure knee graph, and give this change time to
	   take effect before doing autogain. */
	if (sd->autogain && !(sensor_data[sd->sensor].flags & F_COARSE_EXPO)) {
		sd->exposure = EXPOSURE_DEF;
		sd->gain = GAIN_DEF;
		if (gspca_dev->streaming) {
			sd->autogain_ignore_frames = AUTOGAIN_IGNORE_FRAMES;
			setexposure(gspca_dev);
			setgain(gspca_dev);
		}
	}

	return 0;
}