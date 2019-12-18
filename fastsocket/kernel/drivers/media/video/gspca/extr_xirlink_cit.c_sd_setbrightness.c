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
struct sd {scalar_t__ stop_on_control_change; int /*<<< orphan*/  brightness; } ;
struct gspca_dev {scalar_t__ streaming; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  cit_restart_stream (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_set_brightness (struct gspca_dev*) ; 
 int /*<<< orphan*/  sd_stopN (struct gspca_dev*) ; 

__attribute__((used)) static int sd_setbrightness(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->brightness = val;
	if (gspca_dev->streaming) {
		if (sd->stop_on_control_change)
			sd_stopN(gspca_dev);
		cit_set_brightness(gspca_dev);
		if (sd->stop_on_control_change)
			cit_restart_stream(gspca_dev);
	}

	return 0;
}