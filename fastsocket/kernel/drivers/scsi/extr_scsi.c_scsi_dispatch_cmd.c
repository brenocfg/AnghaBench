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
struct scsi_cmnd {int result; int* cmnd; scalar_t__ cmd_len; TYPE_2__* device; } ;
struct Scsi_Host {scalar_t__ max_cmd_len; scalar_t__ shost_state; int /*<<< orphan*/  host_lock; TYPE_1__* hostt; } ;
struct TYPE_4__ {scalar_t__ sdev_state; scalar_t__ scsi_level; int lun; struct Scsi_Host* host; int /*<<< orphan*/  iorequest_cnt; } ;
struct TYPE_3__ {int (* queuecommand ) (struct scsi_cmnd*,int /*<<< orphan*/  (*) (struct scsi_cmnd*)) ;int /*<<< orphan*/  lockless; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int DID_NO_CONNECT ; 
 scalar_t__ SCSI_2 ; 
 int /*<<< orphan*/  SCSI_LOG_MLQUEUE (int,int /*<<< orphan*/ ) ; 
 int SCSI_MLQUEUE_DEVICE_BUSY ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int SCSI_MLQUEUE_TARGET_BUSY ; 
 scalar_t__ SCSI_UNKNOWN ; 
 scalar_t__ SDEV_DEL ; 
 scalar_t__ SHOST_DEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  scsi_cmd_get_serial (struct Scsi_Host*,struct scsi_cmnd*) ; 
 int scsi_device_blocked (TYPE_2__*) ; 
 int /*<<< orphan*/  scsi_done (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_log_send (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_queue_insert (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int stub1 (struct scsi_cmnd*,int /*<<< orphan*/  (*) (struct scsi_cmnd*)) ; 
 int /*<<< orphan*/  trace_scsi_dispatch_cmd_error (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  trace_scsi_dispatch_cmd_start (struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int) ; 

int scsi_dispatch_cmd(struct scsi_cmnd *cmd)
{
	struct Scsi_Host *host = cmd->device->host;
	unsigned long flags = 0;
	int rtn = 0;

	atomic_inc(&cmd->device->iorequest_cnt);

	/* check if the device is still usable */
	if (unlikely(cmd->device->sdev_state == SDEV_DEL)) {
		/* in SDEV_DEL we error all commands. DID_NO_CONNECT
		 * returns an immediate error upwards, and signals
		 * that the device is no longer present */
		cmd->result = DID_NO_CONNECT << 16;
		scsi_done(cmd);
		/* return 0 (because the command has been processed) */
		goto out;
	}

	/* Check to see if the scsi lld made this device blocked. */
	if (unlikely(scsi_device_blocked(cmd->device))) {
		/* 
		 * in blocked state, the command is just put back on
		 * the device queue.  The suspend state has already
		 * blocked the queue so future requests should not
		 * occur until the device transitions out of the
		 * suspend state.
		 */

		scsi_queue_insert(cmd, SCSI_MLQUEUE_DEVICE_BUSY);

		SCSI_LOG_MLQUEUE(3, printk("queuecommand : device blocked \n"));

		/*
		 * NOTE: rtn is still zero here because we don't need the
		 * queue to be plugged on return (it's already stopped)
		 */
		goto out;
	}

	/* 
	 * If SCSI-2 or lower, store the LUN value in cmnd.
	 */
	if (cmd->device->scsi_level <= SCSI_2 &&
	    cmd->device->scsi_level != SCSI_UNKNOWN) {
		cmd->cmnd[1] = (cmd->cmnd[1] & 0x1f) |
			       (cmd->device->lun << 5 & 0xe0);
	}

	scsi_log_send(cmd);

	/*
	 * Before we queue this command, check if the command
	 * length exceeds what the host adapter can handle.
	 */
	if (cmd->cmd_len > cmd->device->host->max_cmd_len) {
		SCSI_LOG_MLQUEUE(3,
			printk("queuecommand : command too long. "
			       "cdb_size=%d host->max_cmd_len=%d\n",
			       cmd->cmd_len, cmd->device->host->max_cmd_len));
		cmd->result = (DID_ABORT << 16);

		scsi_done(cmd);
		goto out;
	}

	if (!host->hostt->lockless) {
		spin_lock_irqsave(host->host_lock, flags);
		/*
		 * AK: unlikely race here: for some reason the timer could
		 * expire before the serial number is set up below.
		 *
		 * TODO: kill serial or move to blk layer
		 */
		scsi_cmd_get_serial(host, cmd); 
	}

	if (unlikely(host->shost_state == SHOST_DEL)) {
		cmd->result = (DID_NO_CONNECT << 16);
		scsi_done(cmd);
	} else {
		trace_scsi_dispatch_cmd_start(cmd);
		rtn = host->hostt->queuecommand(cmd, scsi_done);
	}

	if (!host->hostt->lockless)
		spin_unlock_irqrestore(host->host_lock, flags);

	if (rtn) {
		trace_scsi_dispatch_cmd_error(cmd, rtn);
		if (rtn != SCSI_MLQUEUE_DEVICE_BUSY &&
		    rtn != SCSI_MLQUEUE_TARGET_BUSY)
			rtn = SCSI_MLQUEUE_HOST_BUSY;

		scsi_queue_insert(cmd, rtn);

		SCSI_LOG_MLQUEUE(3,
		    printk("queuecommand : request rejected\n"));
	}

 out:
	SCSI_LOG_MLQUEUE(3, printk("leaving scsi_dispatch_cmnd()\n"));
	return rtn;
}