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
struct ata_device {scalar_t__ sdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEV_OFFLINE ; 
 int /*<<< orphan*/  scsi_device_set_state (scalar_t__,int /*<<< orphan*/ ) ; 

int ata_scsi_offline_dev(struct ata_device *dev)
{
	if (dev->sdev) {
		scsi_device_set_state(dev->sdev, SDEV_OFFLINE);
		return 1;
	}
	return 0;
}