#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct video_device {int minor; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; int /*<<< orphan*/  parent; int /*<<< orphan*/  release; } ;
struct TYPE_6__ {TYPE_2__* slave; } ;
struct v4l2_int_device {TYPE_3__ u; } ;
struct omap24xxcam_device {int /*<<< orphan*/  dev; struct video_device* vfd; struct v4l2_int_device* sdev; } ;
struct TYPE_5__ {TYPE_1__* master; } ;
struct TYPE_4__ {struct omap24xxcam_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_NAME ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_attr_streaming ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap24xxcam_device_unregister (struct v4l2_int_device*) ; 
 int /*<<< orphan*/  omap24xxcam_fops ; 
 int /*<<< orphan*/  omap24xxcam_hwinit (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_ioctl_fops ; 
 int /*<<< orphan*/  omap24xxcam_poweron_reset (struct omap24xxcam_device*) ; 
 int omap24xxcam_sensor_init (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release ; 
 int /*<<< orphan*/  video_nr ; 
 scalar_t__ video_register_device (struct video_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap24xxcam_device_register(struct v4l2_int_device *s)
{
	struct omap24xxcam_device *cam = s->u.slave->master->priv;
	struct video_device *vfd;
	int rval;

	/* We already have a slave. */
	if (cam->sdev)
		return -EBUSY;

	cam->sdev = s;

	if (device_create_file(cam->dev, &dev_attr_streaming) != 0) {
		dev_err(cam->dev, "could not register sysfs entry\n");
		rval = -EBUSY;
		goto err;
	}

	/* initialize the video_device struct */
	vfd = cam->vfd = video_device_alloc();
	if (!vfd) {
		dev_err(cam->dev, "could not allocate video device struct\n");
		rval = -ENOMEM;
		goto err;
	}
	vfd->release = video_device_release;

	vfd->parent = cam->dev;

	strlcpy(vfd->name, CAM_NAME, sizeof(vfd->name));
	vfd->fops		 = &omap24xxcam_fops;
	vfd->minor		 = -1;
	vfd->ioctl_ops		 = &omap24xxcam_ioctl_fops;

	omap24xxcam_hwinit(cam);

	rval = omap24xxcam_sensor_init(cam);
	if (rval)
		goto err;

	if (video_register_device(vfd, VFL_TYPE_GRABBER, video_nr) < 0) {
		dev_err(cam->dev, "could not register V4L device\n");
		vfd->minor = -1;
		rval = -EBUSY;
		goto err;
	}

	omap24xxcam_poweron_reset(cam);

	dev_info(cam->dev, "registered device video%d\n", vfd->minor);

	return 0;

err:
	omap24xxcam_device_unregister(s);

	return rval;
}