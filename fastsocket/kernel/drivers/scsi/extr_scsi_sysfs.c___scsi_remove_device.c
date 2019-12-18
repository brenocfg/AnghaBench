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
struct device {int dummy; } ;
struct scsi_device {TYPE_2__* host; int /*<<< orphan*/  requeue_work; int /*<<< orphan*/  request_queue; struct device sdev_dev; scalar_t__ is_visible; struct device sdev_gendev; } ;
struct TYPE_4__ {TYPE_1__* hostt; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* slave_destroy ) (struct scsi_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SDEV_CANCEL ; 
 int /*<<< orphan*/  SDEV_DEL ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsg_unregister_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 scalar_t__ scsi_device_set_state (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_device*) ; 
 int /*<<< orphan*/  transport_destroy_device (struct device*) ; 
 int /*<<< orphan*/  transport_remove_device (struct device*) ; 

void __scsi_remove_device(struct scsi_device *sdev)
{
	struct device *dev = &sdev->sdev_gendev;

	if (sdev->is_visible) {
		if (scsi_device_set_state(sdev, SDEV_CANCEL) != 0)
			return;

		bsg_unregister_queue(sdev->request_queue);
		device_unregister(&sdev->sdev_dev);
		transport_remove_device(dev);
		device_del(dev);
	} else
		put_device(&sdev->sdev_dev);

	/*
	 * Stop accepting new requests and wait until all queuecommand() and
	 * scsi_run_queue() invocations have finished before tearing down the
	 * device.
	 */
	scsi_device_set_state(sdev, SDEV_DEL);
	blk_cleanup_queue(sdev->request_queue);
	cancel_work_sync(&sdev->requeue_work);

	if (sdev->host->hostt->slave_destroy)
		sdev->host->hostt->slave_destroy(sdev);
	transport_destroy_device(dev);

	put_device(dev);
}