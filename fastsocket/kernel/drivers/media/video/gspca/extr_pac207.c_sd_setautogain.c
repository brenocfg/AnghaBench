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
struct sd {int /*<<< orphan*/  autogain_ignore_frames; int /*<<< orphan*/  gain; int /*<<< orphan*/  exposure; scalar_t__ autogain; } ;
struct gspca_dev {scalar_t__ streaming; } ;
typedef  scalar_t__ __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  PAC207_EXPOSURE_DEFAULT ; 
 int /*<<< orphan*/  PAC207_GAIN_DEFAULT ; 
 int /*<<< orphan*/  PAC_AUTOGAIN_IGNORE_FRAMES ; 
 int /*<<< orphan*/  setexposure (struct gspca_dev*) ; 
 int /*<<< orphan*/  setgain (struct gspca_dev*) ; 

__attribute__((used)) static int sd_setautogain(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->autogain = val;
	/* when switching to autogain set defaults to make sure
	   we are on a valid point of the autogain gain /
	   exposure knee graph, and give this change time to
	   take effect before doing autogain. */
	if (sd->autogain) {
		sd->exposure = PAC207_EXPOSURE_DEFAULT;
		sd->gain = PAC207_GAIN_DEFAULT;
		if (gspca_dev->streaming) {
			sd->autogain_ignore_frames =
				PAC_AUTOGAIN_IGNORE_FRAMES;
			setexposure(gspca_dev);
			setgain(gspca_dev);
		}
	}

	return 0;
}