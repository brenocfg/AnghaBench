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
struct hv_driver {int /*<<< orphan*/  (* remove ) (struct hv_device*) ;} ;
struct hv_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct hv_device* device_to_hv_device (struct device*) ; 
 struct hv_driver* drv_to_hv_drv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hv_device*) ; 

__attribute__((used)) static int vmbus_remove(struct device *child_device)
{
	struct hv_driver *drv = drv_to_hv_drv(child_device->driver);
	struct hv_device *dev = device_to_hv_device(child_device);

	if (drv->remove)
		drv->remove(dev);
	else
		pr_err("remove not set for driver %s\n",
			dev_name(child_device));

	return 0;
}