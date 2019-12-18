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
struct scsi_cmnd {struct request* request; struct scsi_device* device; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_requeue_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_run_queue (struct request_queue*) ; 
 int /*<<< orphan*/  scsi_unprep_request (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void scsi_requeue_command(struct request_queue *q, struct scsi_cmnd *cmd)
{
	struct scsi_device *sdev = cmd->device;
	struct request *req = cmd->request;
	unsigned long flags;

	/*
	 * We need to hold a reference on the device to avoid the queue being
	 * killed after the unlock and before scsi_run_queue is invoked which
	 * may happen because scsi_unprep_request() puts the command which
	 * releases its reference on the device.
	 */
	get_device(&sdev->sdev_gendev);

	spin_lock_irqsave(q->queue_lock, flags);
	scsi_unprep_request(req);
	blk_requeue_request(q, req);
	spin_unlock_irqrestore(q->queue_lock, flags);

	scsi_run_queue(q);

	put_device(&sdev->sdev_gendev);
}