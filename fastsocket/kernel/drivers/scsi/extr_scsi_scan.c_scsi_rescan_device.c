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
struct scsi_driver {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* rescan ) (struct device*) ;} ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 struct scsi_driver* to_scsi_driver (int /*<<< orphan*/ ) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

void scsi_rescan_device(struct device *dev)
{
	struct scsi_driver *drv;
	
	if (!dev->driver)
		return;

	drv = to_scsi_driver(dev->driver);
	if (try_module_get(drv->owner)) {
		if (drv->rescan)
			drv->rescan(dev);
		module_put(drv->owner);
	}
}