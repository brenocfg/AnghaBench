#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ owner; } ;
struct TYPE_3__ {struct scsi_device* scsi_device; } ;
struct osd_uld_device {TYPE_2__ cdev; int /*<<< orphan*/  minor; scalar_t__ class_member; TYPE_1__ od; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSD_ERR (char*,struct device*,struct osd_uld_device*,struct scsi_device*,struct scsi_device*) ; 
 int /*<<< orphan*/  SCSI_OSD_MAJOR ; 
 int /*<<< orphan*/  __uld_put (struct osd_uld_device*) ; 
 int /*<<< orphan*/  cdev_del (TYPE_2__*) ; 
 struct osd_uld_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_sysfs_class ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int osd_remove(struct device *dev)
{
	struct scsi_device *scsi_device = to_scsi_device(dev);
	struct osd_uld_device *oud = dev_get_drvdata(dev);

	if (!oud || (oud->od.scsi_device != scsi_device)) {
		OSD_ERR("Half cooked osd-device %p,%p || %p!=%p",
			dev, oud, oud ? oud->od.scsi_device : NULL,
			scsi_device);
	}

	if (oud->class_member)
		device_destroy(osd_sysfs_class,
			       MKDEV(SCSI_OSD_MAJOR, oud->minor));

	/* We have 2 references to the cdev. One is released here
	 * and also takes down the /dev/osdX mapping. The second
	 * Will be released in __remove() after all users have released
	 * the osd_uld_device.
	 */
	if (oud->cdev.owner)
		cdev_del(&oud->cdev);

	__uld_put(oud);
	return 0;
}