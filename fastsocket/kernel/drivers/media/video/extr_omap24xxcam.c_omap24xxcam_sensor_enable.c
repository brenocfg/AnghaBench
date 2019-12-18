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
struct omap24xxcam_device {int /*<<< orphan*/  sdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap24xxcam_clock_on (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_sensor_disable (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_sensor_if_enable (struct omap24xxcam_device*) ; 
 int vidioc_int_init (int /*<<< orphan*/ ) ; 
 int vidioc_int_s_power (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int omap24xxcam_sensor_enable(struct omap24xxcam_device *cam)
{
	int rval;

	omap24xxcam_clock_on(cam);

	omap24xxcam_sensor_if_enable(cam);

	rval = vidioc_int_s_power(cam->sdev, 1);
	if (rval)
		goto out;

	rval = vidioc_int_init(cam->sdev);
	if (rval)
		goto out;

	return 0;

out:
	omap24xxcam_sensor_disable(cam);

	return rval;
}