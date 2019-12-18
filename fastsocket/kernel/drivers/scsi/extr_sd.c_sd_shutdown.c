#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_disk {TYPE_1__* device; scalar_t__ WCE; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ manage_start_stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOTICE ; 
 scalar_t__ SYSTEM_RESTART ; 
 struct scsi_disk* scsi_disk_get_from_dev (struct device*) ; 
 int /*<<< orphan*/  scsi_disk_put (struct scsi_disk*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 
 int /*<<< orphan*/  sd_start_stop_device (struct scsi_disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_sync_cache (struct scsi_disk*) ; 
 scalar_t__ system_state ; 

__attribute__((used)) static void sd_shutdown(struct device *dev)
{
	struct scsi_disk *sdkp = scsi_disk_get_from_dev(dev);

	if (!sdkp)
		return;         /* this can happen */

	if (sdkp->WCE) {
		sd_printk(KERN_NOTICE, sdkp, "Synchronizing SCSI cache\n");
		sd_sync_cache(sdkp);
	}

	if (system_state != SYSTEM_RESTART && sdkp->device->manage_start_stop) {
		sd_printk(KERN_NOTICE, sdkp, "Stopping disk\n");
		sd_start_stop_device(sdkp, 0);
	}

	scsi_disk_put(sdkp);
}