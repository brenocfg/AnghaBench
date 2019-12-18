#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* slave; } ;
struct v4l2_int_device {TYPE_3__ u; } ;
struct omap24xxcam_device {int /*<<< orphan*/ * sdev; int /*<<< orphan*/  dev; TYPE_4__* vfd; } ;
struct TYPE_9__ {int minor; } ;
struct TYPE_7__ {TYPE_1__* master; } ;
struct TYPE_6__ {struct omap24xxcam_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_streaming ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap24xxcam_sensor_exit (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  video_device_release (TYPE_4__*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_4__*) ; 

__attribute__((used)) static void omap24xxcam_device_unregister(struct v4l2_int_device *s)
{
	struct omap24xxcam_device *cam = s->u.slave->master->priv;

	omap24xxcam_sensor_exit(cam);

	if (cam->vfd) {
		if (cam->vfd->minor == -1) {
			/*
			 * The device was never registered, so release the
			 * video_device struct directly.
			 */
			video_device_release(cam->vfd);
		} else {
			/*
			 * The unregister function will release the
			 * video_device struct as well as
			 * unregistering it.
			 */
			video_unregister_device(cam->vfd);
		}
		cam->vfd = NULL;
	}

	device_remove_file(cam->dev, &dev_attr_streaming);

	cam->sdev = NULL;
}