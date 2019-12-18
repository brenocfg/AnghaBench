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
struct scsi_device {int /*<<< orphan*/  sdev_gendev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_dh_state_attr ; 
 int /*<<< orphan*/  scsi_is_sdev_device (struct device*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int scsi_dh_sysfs_attr_add(struct device *dev, void *data)
{
	struct scsi_device *sdev;
	int err;

	if (!scsi_is_sdev_device(dev))
		return 0;

	sdev = to_scsi_device(dev);

	err = device_create_file(&sdev->sdev_gendev,
				 &scsi_dh_state_attr);

	return 0;
}