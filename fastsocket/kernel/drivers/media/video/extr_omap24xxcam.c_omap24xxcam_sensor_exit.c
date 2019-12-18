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
struct omap24xxcam_device {scalar_t__ sdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  vidioc_int_dev_exit (scalar_t__) ; 

__attribute__((used)) static void omap24xxcam_sensor_exit(struct omap24xxcam_device *cam)
{
	if (cam->sdev)
		vidioc_int_dev_exit(cam->sdev);
}