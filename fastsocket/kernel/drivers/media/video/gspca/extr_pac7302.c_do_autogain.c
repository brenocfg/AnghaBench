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
struct sd {int brightness; scalar_t__ autogain_ignore_frames; int /*<<< orphan*/  avg_lum; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPOSURE_KNEE ; 
 int /*<<< orphan*/  GAIN_KNEE ; 
 scalar_t__ PAC_AUTOGAIN_IGNORE_FRAMES ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ gspca_auto_gain_n_exposure (struct gspca_dev*,int,int,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_autogain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int avg_lum = atomic_read(&sd->avg_lum);
	int desired_lum;
	const int deadzone = 30;

	if (avg_lum == -1)
		return;

	desired_lum = 270 + sd->brightness;

	if (sd->autogain_ignore_frames > 0)
		sd->autogain_ignore_frames--;
	else if (gspca_auto_gain_n_exposure(gspca_dev, avg_lum, desired_lum,
			deadzone, GAIN_KNEE, EXPOSURE_KNEE))
		sd->autogain_ignore_frames = PAC_AUTOGAIN_IGNORE_FRAMES;
}