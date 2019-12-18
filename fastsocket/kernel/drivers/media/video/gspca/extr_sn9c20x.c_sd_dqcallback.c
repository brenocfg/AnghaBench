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
struct sd {scalar_t__ sensor; int /*<<< orphan*/  avg_lum; int /*<<< orphan*/  auto_exposure; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ SENSOR_SOI968 ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_autoexposure (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  do_autogain (struct gspca_dev*,int) ; 

__attribute__((used)) static void sd_dqcallback(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int avg_lum;

	if (!sd->auto_exposure)
		return;

	avg_lum = atomic_read(&sd->avg_lum);
	if (sd->sensor == SENSOR_SOI968)
		do_autogain(gspca_dev, avg_lum);
	else
		do_autoexposure(gspca_dev, avg_lum);
}