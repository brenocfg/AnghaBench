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
struct scsi_disk {TYPE_1__* device; int /*<<< orphan*/  index; struct gendisk* disk; } ;
struct gendisk {int /*<<< orphan*/ * private_data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sdev_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scsi_disk*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  sd_index_ida ; 
 int /*<<< orphan*/  sd_index_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct scsi_disk* to_scsi_disk (struct device*) ; 

__attribute__((used)) static void scsi_disk_release(struct device *dev)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	struct gendisk *disk = sdkp->disk;
	
	spin_lock(&sd_index_lock);
	ida_remove(&sd_index_ida, sdkp->index);
	spin_unlock(&sd_index_lock);

	disk->private_data = NULL;
	put_disk(disk);
	put_device(&sdkp->device->sdev_gendev);

	kfree(sdkp);
}