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
struct scsi_target {int /*<<< orphan*/  max_target_blocked; int /*<<< orphan*/  target_blocked; } ;
struct scsi_device {int /*<<< orphan*/  requeue_work; int /*<<< orphan*/  max_device_blocked; int /*<<< orphan*/  device_blocked; struct request_queue* request_queue; struct Scsi_Host* host; } ;
struct scsi_cmnd {int /*<<< orphan*/  request; struct scsi_device* device; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct Scsi_Host {int /*<<< orphan*/  max_host_blocked; int /*<<< orphan*/  host_blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_LOG_MLQUEUE (int,int /*<<< orphan*/ ) ; 
#define  SCSI_MLQUEUE_DEVICE_BUSY 131 
#define  SCSI_MLQUEUE_EH_RETRY 130 
#define  SCSI_MLQUEUE_HOST_BUSY 129 
#define  SCSI_MLQUEUE_TARGET_BUSY 128 
 int /*<<< orphan*/  blk_requeue_request (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kblockd_schedule_work (struct request_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_device_unbusy (struct scsi_device*) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void __scsi_queue_insert(struct scsi_cmnd *cmd, int reason, int unbusy)
{
	struct Scsi_Host *host = cmd->device->host;
	struct scsi_device *device = cmd->device;
	struct scsi_target *starget = scsi_target(device);
	struct request_queue *q = device->request_queue;
	unsigned long flags;

	SCSI_LOG_MLQUEUE(1,
		 printk("Inserting command %p into mlqueue\n", cmd));

	/*
	 * Set the appropriate busy bit for the device/host.
	 *
	 * If the host/device isn't busy, assume that something actually
	 * completed, and that we should be able to queue a command now.
	 *
	 * Note that the prior mid-layer assumption that any host could
	 * always queue at least one command is now broken.  The mid-layer
	 * will implement a user specifiable stall (see
	 * scsi_host.max_host_blocked and scsi_device.max_device_blocked)
	 * if a command is requeued with no other commands outstanding
	 * either for the device or for the host.
	 */
	switch (reason) {
	case SCSI_MLQUEUE_HOST_BUSY:
		host->host_blocked = host->max_host_blocked;
		break;
	case SCSI_MLQUEUE_DEVICE_BUSY:
	case SCSI_MLQUEUE_EH_RETRY:
		device->device_blocked = device->max_device_blocked;
		break;
	case SCSI_MLQUEUE_TARGET_BUSY:
		starget->target_blocked = starget->max_target_blocked;
		break;
	}

	/*
	 * Decrement the counters, since these commands are no longer
	 * active on the host/device.
	 */
	if (unbusy)
		scsi_device_unbusy(device);

	/*
	 * Requeue this command.  It will go before all other commands
	 * that are already in the queue. Schedule requeue work under
	 * lock such that the kblockd_schedule_work() call happens
	 * before blk_cleanup_queue() finishes.
         */
	spin_lock_irqsave(q->queue_lock, flags);
	blk_requeue_request(q, cmd->request);
	kblockd_schedule_work(q, &device->requeue_work);
	spin_unlock_irqrestore(q->queue_lock, flags);
}