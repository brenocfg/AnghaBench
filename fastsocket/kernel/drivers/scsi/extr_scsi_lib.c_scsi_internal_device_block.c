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
struct scsi_device {struct request_queue* request_queue; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEV_BLOCK ; 
 int /*<<< orphan*/  SDEV_CREATED_BLOCK ; 
 int /*<<< orphan*/  blk_stop_queue (struct request_queue*) ; 
 int scsi_device_set_state (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

int
scsi_internal_device_block(struct scsi_device *sdev)
{
	struct request_queue *q = sdev->request_queue;
	unsigned long flags;
	int err = 0;

	err = scsi_device_set_state(sdev, SDEV_BLOCK);
	if (err) {
		err = scsi_device_set_state(sdev, SDEV_CREATED_BLOCK);

		if (err)
			return err;
	}

	/* 
	 * The device has transitioned to SDEV_BLOCK.  Stop the
	 * block layer from calling the midlayer with this device's
	 * request queue. 
	 */
	spin_lock_irqsave(q->queue_lock, flags);
	blk_stop_queue(q);
	spin_unlock_irqrestore(q->queue_lock, flags);

	return 0;
}