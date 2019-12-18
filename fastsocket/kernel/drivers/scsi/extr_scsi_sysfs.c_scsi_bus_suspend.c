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
struct scsi_device {int dummy; } ;
struct device_driver {int (* suspend ) (struct device*,int /*<<< orphan*/ ) ;} ;
struct device {struct device_driver* driver; int /*<<< orphan*/ * type; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_dev_type ; 
 int scsi_device_quiesce (struct scsi_device*) ; 
 int stub1 (struct device*,int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int scsi_bus_suspend(struct device * dev, pm_message_t state)
{
	struct device_driver *drv;
	struct scsi_device *sdev;
	int err;

	if (dev->type != &scsi_dev_type)
		return 0;

	drv = dev->driver;
	sdev = to_scsi_device(dev);

	err = scsi_device_quiesce(sdev);
	if (err)
		return err;

	if (drv && drv->suspend) {
		err = drv->suspend(dev, state);
		if (err)
			return err;
	}

	return 0;
}