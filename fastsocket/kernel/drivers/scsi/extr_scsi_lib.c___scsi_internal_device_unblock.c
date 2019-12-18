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
struct scsi_device {scalar_t__ sdev_state; struct request_queue* request_queue; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
typedef  enum scsi_device_state { ____Placeholder_scsi_device_state } scsi_device_state ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SDEV_BLOCK ; 
 scalar_t__ SDEV_CANCEL ; 
 int SDEV_CREATED ; 
 scalar_t__ SDEV_CREATED_BLOCK ; 
 int SDEV_OFFLINE ; 
 scalar_t__ SDEV_TRANSPORT_OFFLINE ; 
 int /*<<< orphan*/  blk_start_queue (struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

int
__scsi_internal_device_unblock(struct scsi_device *sdev,
			     enum scsi_device_state new_state)
{
	struct request_queue *q = sdev->request_queue; 
	unsigned long flags;

	/*
	 * Try to transition the scsi device to SDEV_RUNNING or one of the
	 * offlined states and goose the device queue if successful.
	 */
	if ((sdev->sdev_state == SDEV_BLOCK) ||
	    (sdev->sdev_state == SDEV_TRANSPORT_OFFLINE))
		sdev->sdev_state = new_state;
	else if (sdev->sdev_state == SDEV_CREATED_BLOCK) {
		if (new_state == SDEV_TRANSPORT_OFFLINE ||
		    new_state == SDEV_OFFLINE)
			sdev->sdev_state = new_state;
		else
			sdev->sdev_state = SDEV_CREATED;
	} else if (sdev->sdev_state != SDEV_CANCEL &&
		 sdev->sdev_state != SDEV_OFFLINE)
		return -EINVAL;

	spin_lock_irqsave(q->queue_lock, flags);
	blk_start_queue(q);
	spin_unlock_irqrestore(q->queue_lock, flags);

	return 0;
}