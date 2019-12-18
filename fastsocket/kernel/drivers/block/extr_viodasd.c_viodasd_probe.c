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
struct viodasd_device {int /*<<< orphan*/ * dev; } ;
struct vio_device_id {int dummy; } ;
struct vio_dev {size_t unit_address; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  probe_disk (struct viodasd_device*) ; 
 struct viodasd_device* viodasd_devices ; 

__attribute__((used)) static int viodasd_probe(struct vio_dev *vdev, const struct vio_device_id *id)
{
	struct viodasd_device *d = &viodasd_devices[vdev->unit_address];

	d->dev = &vdev->dev;
	if (!probe_disk(d))
		return -ENODEV;
	return 0;
}