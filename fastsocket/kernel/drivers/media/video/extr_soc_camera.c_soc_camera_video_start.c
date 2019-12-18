#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {TYPE_3__* vdev; TYPE_4__ dev; TYPE_1__* ops; } ;
struct device_type {int dummy; } ;
struct TYPE_6__ {struct device_type* type; } ;
struct TYPE_7__ {TYPE_2__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  set_bus_param; int /*<<< orphan*/  query_bus_param; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 int video_register_device (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int soc_camera_video_start(struct soc_camera_device *icd)
{
	struct device_type *type = icd->vdev->dev.type;
	int ret;

	if (!icd->dev.parent)
		return -ENODEV;

	if (!icd->ops ||
	    !icd->ops->query_bus_param ||
	    !icd->ops->set_bus_param)
		return -EINVAL;

	ret = video_register_device(icd->vdev, VFL_TYPE_GRABBER, -1);
	if (ret < 0) {
		dev_err(&icd->dev, "video_register_device failed: %d\n", ret);
		return ret;
	}

	/* Restore device type, possibly set by the subdevice driver */
	icd->vdev->dev.type = type;

	return 0;
}