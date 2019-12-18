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
struct scsi_disk {int /*<<< orphan*/  dev; int /*<<< orphan*/  disk; TYPE_1__* device; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_synchronize_full_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_prep_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_unprep_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 struct scsi_disk* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_prep_fn ; 
 int /*<<< orphan*/  scsi_sd_probe_domain ; 
 int /*<<< orphan*/  sd_ref_mutex ; 
 int /*<<< orphan*/  sd_shutdown (struct device*) ; 

__attribute__((used)) static int sd_remove(struct device *dev)
{
	struct scsi_disk *sdkp;

	async_synchronize_full_domain(&scsi_sd_probe_domain);
	sdkp = dev_get_drvdata(dev);
	blk_queue_prep_rq(sdkp->device->request_queue, scsi_prep_fn);
	blk_queue_unprep_rq(sdkp->device->request_queue, NULL);
	device_del(&sdkp->dev);
	del_gendisk(sdkp->disk);
	sd_shutdown(dev);

	mutex_lock(&sd_ref_mutex);
	dev_set_drvdata(dev, NULL);
	put_device(&sdkp->dev);
	mutex_unlock(&sd_ref_mutex);

	return 0;
}