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
typedef  scalar_t__ u16 ;
struct sd {int exposure; int exposure_step; int older_step; int old_step; } ;
struct gspca_dev {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 scalar_t__ MAX_AVG_LUM ; 
 scalar_t__ MIN_AVG_LUM ; 
 int /*<<< orphan*/  set_exposure (struct gspca_dev*) ; 

__attribute__((used)) static void do_autoexposure(struct gspca_dev *gspca_dev, u16 avg_lum)
{
	struct sd *sd = (struct sd *) gspca_dev;
	s16 new_exp;

	/*
	 * some hardcoded values are present
	 * like those for maximal/minimal exposure
	 * and exposure steps
	 */
	if (avg_lum < MIN_AVG_LUM) {
		if (sd->exposure > 0x1770)
			return;

		new_exp = sd->exposure + sd->exposure_step;
		if (new_exp > 0x1770)
			new_exp = 0x1770;
		if (new_exp < 0x10)
			new_exp = 0x10;
		sd->exposure = new_exp;
		set_exposure(gspca_dev);

		sd->older_step = sd->old_step;
		sd->old_step = 1;

		if (sd->old_step ^ sd->older_step)
			sd->exposure_step /= 2;
		else
			sd->exposure_step += 2;
	}
	if (avg_lum > MAX_AVG_LUM) {
		if (sd->exposure < 0x10)
			return;
		new_exp = sd->exposure - sd->exposure_step;
		if (new_exp > 0x1700)
			new_exp = 0x1770;
		if (new_exp < 0x10)
			new_exp = 0x10;
		sd->exposure = new_exp;
		set_exposure(gspca_dev);
		sd->older_step = sd->old_step;
		sd->old_step = 0;

		if (sd->old_step ^ sd->older_step)
			sd->exposure_step /= 2;
		else
			sd->exposure_step += 2;
	}
}