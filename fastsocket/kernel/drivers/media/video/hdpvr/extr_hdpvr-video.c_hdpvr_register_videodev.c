#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hdpvr_device {int /*<<< orphan*/  v4l2_dev; TYPE_1__* video_dev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* parent; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 TYPE_1__ hdpvr_video_template ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* video_device_alloc () ; 
 scalar_t__ video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct hdpvr_device*) ; 

int hdpvr_register_videodev(struct hdpvr_device *dev, struct device *parent,
			    int devnum)
{
	/* setup and register video device */
	dev->video_dev = video_device_alloc();
	if (!dev->video_dev) {
		v4l2_err(&dev->v4l2_dev, "video_device_alloc() failed\n");
		goto error;
	}

	*(dev->video_dev) = hdpvr_video_template;
	strcpy(dev->video_dev->name, "Hauppauge HD PVR");
	dev->video_dev->parent = parent;
	video_set_drvdata(dev->video_dev, dev);

	if (video_register_device(dev->video_dev, VFL_TYPE_GRABBER, devnum)) {
		v4l2_err(&dev->v4l2_dev, "video_device registration failed\n");
		goto error;
	}

	return 0;
error:
	return -ENOMEM;
}