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
struct scsi_cmnd {int allowed; TYPE_1__* device; scalar_t__ jiffies_at_alloc; scalar_t__ result; scalar_t__ serial_number; int /*<<< orphan*/  eh_entry; } ;
struct request {int timeout; struct scsi_cmnd* special; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioerr_cnt; int /*<<< orphan*/  iodone_cnt; } ;

/* Variables and functions */
#define  ADD_TO_MLQUEUE 130 
 unsigned long HZ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_ERR ; 
#define  NEEDS_RETRY 129 
 int /*<<< orphan*/  SCSI_MLQUEUE_DEVICE_BUSY ; 
 int /*<<< orphan*/  SCSI_MLQUEUE_EH_RETRY ; 
#define  SUCCESS 128 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int scsi_decide_disposition (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_eh_scmd_add (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_finish_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_log_completion (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  scsi_queue_insert (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,TYPE_1__*,char*,unsigned long) ; 
 scalar_t__ time_before (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsi_softirq_done(struct request *rq)
{
	struct scsi_cmnd *cmd = rq->special;
	unsigned long wait_for = (cmd->allowed + 1) * rq->timeout;
	int disposition;

	INIT_LIST_HEAD(&cmd->eh_entry);

	/*
	 * Set the serial numbers back to zero
	 */
	cmd->serial_number = 0;

	atomic_inc(&cmd->device->iodone_cnt);
	if (cmd->result)
		atomic_inc(&cmd->device->ioerr_cnt);

	disposition = scsi_decide_disposition(cmd);
	if (disposition != SUCCESS &&
	    time_before(cmd->jiffies_at_alloc + wait_for, jiffies)) {
		sdev_printk(KERN_ERR, cmd->device,
			    "timing out command, waited %lus\n",
			    wait_for/HZ);
		disposition = SUCCESS;
	}
			
	scsi_log_completion(cmd, disposition);

	switch (disposition) {
		case SUCCESS:
			scsi_finish_command(cmd);
			break;
		case NEEDS_RETRY:
			scsi_queue_insert(cmd, SCSI_MLQUEUE_EH_RETRY);
			break;
		case ADD_TO_MLQUEUE:
			scsi_queue_insert(cmd, SCSI_MLQUEUE_DEVICE_BUSY);
			break;
		default:
			if (!scsi_eh_scmd_add(cmd, 0))
				scsi_finish_command(cmd);
	}
}