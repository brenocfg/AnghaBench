#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int queue_depth; int ordered_tags; int simple_tags; TYPE_2__* request_queue; TYPE_1__* host; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  bqt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
#define  MSG_ORDERED_TAG 129 
#define  MSG_SIMPLE_TAG 128 
 scalar_t__ blk_queue_resize_tags (TYPE_2__*,int) ; 
 scalar_t__ blk_queue_tagged (TYPE_2__*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void scsi_adjust_queue_depth(struct scsi_device *sdev, int tagged, int tags)
{
	unsigned long flags;

	/*
	 * refuse to set tagged depth to an unworkable size
	 */
	if (tags <= 0)
		return;

	spin_lock_irqsave(sdev->request_queue->queue_lock, flags);

	/*
	 * Check to see if the queue is managed by the block layer.
	 * If it is, and we fail to adjust the depth, exit.
	 *
	 * Do not resize the tag map if it is a host wide share bqt,
	 * because the size should be the hosts's can_queue. If there
	 * is more IO than the LLD's can_queue (so there are not enuogh
	 * tags) request_fn's host queue ready check will handle it.
	 */
	if (!sdev->host->bqt) {
		if (blk_queue_tagged(sdev->request_queue) &&
		    blk_queue_resize_tags(sdev->request_queue, tags) != 0)
			goto out;
	}

	sdev->queue_depth = tags;
	switch (tagged) {
		case MSG_ORDERED_TAG:
			sdev->ordered_tags = 1;
			sdev->simple_tags = 1;
			break;
		case MSG_SIMPLE_TAG:
			sdev->ordered_tags = 0;
			sdev->simple_tags = 1;
			break;
		default:
			sdev_printk(KERN_WARNING, sdev,
				    "scsi_adjust_queue_depth, bad queue type, "
				    "disabled\n");
		case 0:
			sdev->ordered_tags = sdev->simple_tags = 0;
			sdev->queue_depth = tags;
			break;
	}
 out:
	spin_unlock_irqrestore(sdev->request_queue->queue_lock, flags);
}