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
struct vio_driver {int (* remove ) (struct vio_dev*) ;} ;
struct vio_dev {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int stub1 (struct vio_dev*) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 
 struct vio_driver* to_vio_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vio_device_remove(struct device *dev)
{
	struct vio_dev *vdev = to_vio_dev(dev);
	struct vio_driver *drv = to_vio_driver(dev->driver);

	if (drv->remove)
		return drv->remove(vdev);

	return 1;
}