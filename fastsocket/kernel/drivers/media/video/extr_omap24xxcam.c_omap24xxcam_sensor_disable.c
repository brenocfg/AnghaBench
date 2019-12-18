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
 int /*<<< orphan*/  omap24xxcam_clock_off (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_sensor_if_disable (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  vidioc_int_s_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap24xxcam_sensor_disable(struct omap24xxcam_device *cam)
{
	omap24xxcam_sensor_if_disable(cam);
	omap24xxcam_clock_off(cam);
	vidioc_int_s_power(cam->sdev, 0);
}