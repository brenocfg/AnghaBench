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
struct v4l2_int_device {int /*<<< orphan*/  name; } ;
struct omap24xxcam_device {int /*<<< orphan*/  dev; struct v4l2_int_device* sdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap24xxcam_clock_off (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_clock_on (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_sensor_if_disable (struct omap24xxcam_device*) ; 
 int omap24xxcam_sensor_if_enable (struct omap24xxcam_device*) ; 
 int vidioc_int_dev_init (struct v4l2_int_device*) ; 
 int /*<<< orphan*/  vidioc_int_s_power (struct v4l2_int_device*,int) ; 

__attribute__((used)) static int omap24xxcam_sensor_init(struct omap24xxcam_device *cam)
{
	int err = 0;
	struct v4l2_int_device *sdev = cam->sdev;

	omap24xxcam_clock_on(cam);
	err = omap24xxcam_sensor_if_enable(cam);
	if (err) {
		dev_err(cam->dev, "sensor interface could not be enabled at "
			"initialisation, %d\n", err);
		cam->sdev = NULL;
		goto out;
	}

	/* power up sensor during sensor initialization */
	vidioc_int_s_power(sdev, 1);

	err = vidioc_int_dev_init(sdev);
	if (err) {
		dev_err(cam->dev, "cannot initialize sensor, error %d\n", err);
		/* Sensor init failed --- it's nonexistent to us! */
		cam->sdev = NULL;
		goto out;
	}

	dev_info(cam->dev, "sensor is %s\n", sdev->name);

out:
	omap24xxcam_sensor_if_disable(cam);
	omap24xxcam_clock_off(cam);

	vidioc_int_s_power(sdev, 0);

	return err;
}