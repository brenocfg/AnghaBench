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
struct scsi_disk {TYPE_1__* device; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  manage_start_stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOTICE ; 
 struct scsi_disk* scsi_disk_get_from_dev (struct device*) ; 
 int /*<<< orphan*/  scsi_disk_put (struct scsi_disk*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 
 int sd_start_stop_device (struct scsi_disk*,int) ; 

__attribute__((used)) static int sd_resume(struct device *dev)
{
	struct scsi_disk *sdkp = scsi_disk_get_from_dev(dev);
	int ret = 0;

	if (!sdkp->device->manage_start_stop)
		goto done;

	sd_printk(KERN_NOTICE, sdkp, "Starting disk\n");
	ret = sd_start_stop_device(sdkp, 1);

done:
	scsi_disk_put(sdkp);
	return ret;
}