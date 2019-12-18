#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ ioa_state; } ;
struct pmcraid_instance {int ioa_reset_in_progress; TYPE_5__* host; int /*<<< orphan*/  ioa_state; TYPE_4__ scn; struct pmcraid_cmd* reset_cmd; scalar_t__ ioa_reset_attempts; TYPE_1__* pdev; } ;
struct pmcraid_cmd {int /*<<< orphan*/  cmd_done; TYPE_3__* ioa_cb; struct pmcraid_instance* drv_inst; } ;
struct TYPE_10__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_7__ {int /*<<< orphan*/ * cdb; } ;
struct TYPE_8__ {TYPE_2__ ioarcb; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOA_STATE_IN_RESET_ALERT ; 
 scalar_t__ PMC_DEVICE_EVENT_RESET_START ; 
 scalar_t__ PMC_DEVICE_EVENT_SHUTDOWN_START ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_err (char*) ; 
 struct pmcraid_cmd* pmcraid_get_free_cmd (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_info (char*) ; 
 int /*<<< orphan*/  pmcraid_ioa_reset ; 
 int /*<<< orphan*/  pmcraid_notify_ioastate (struct pmcraid_instance*,scalar_t__) ; 
 int /*<<< orphan*/  pmcraid_reset_alert (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  scsi_block_requests (TYPE_5__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void pmcraid_timeout_handler(struct pmcraid_cmd *cmd)
{
	struct pmcraid_instance *pinstance = cmd->drv_inst;
	unsigned long lock_flags;

	dev_info(&pinstance->pdev->dev,
		"Adapter being reset due to cmd(CDB[0] = %x) timeout\n",
		cmd->ioa_cb->ioarcb.cdb[0]);

	/* Command timeouts result in hard reset sequence. The command that got
	 * timed out may be the one used as part of reset sequence. In this
	 * case restart reset sequence using the same command block even if
	 * reset is in progress. Otherwise fail this command and get a free
	 * command block to restart the reset sequence.
	 */
	spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
	if (!pinstance->ioa_reset_in_progress) {
		pinstance->ioa_reset_attempts = 0;
		cmd = pmcraid_get_free_cmd(pinstance);

		/* If we are out of command blocks, just return here itself.
		 * Some other command's timeout handler can do the reset job
		 */
		if (cmd == NULL) {
			spin_unlock_irqrestore(pinstance->host->host_lock,
					       lock_flags);
			pmcraid_err("no free cmnd block for timeout handler\n");
			return;
		}

		pinstance->reset_cmd = cmd;
		pinstance->ioa_reset_in_progress = 1;
	} else {
		pmcraid_info("reset is already in progress\n");

		if (pinstance->reset_cmd != cmd) {
			/* This command should have been given to IOA, this
			 * command will be completed by fail_outstanding_cmds
			 * anyway
			 */
			pmcraid_err("cmd is pending but reset in progress\n");
		}

		/* If this command was being used as part of the reset
		 * sequence, set cmd_done pointer to pmcraid_ioa_reset. This
		 * causes fail_outstanding_commands not to return the command
		 * block back to free pool
		 */
		if (cmd == pinstance->reset_cmd)
			cmd->cmd_done = pmcraid_ioa_reset;
	}

	/* Notify apps of important IOA bringup/bringdown sequences */
	if (pinstance->scn.ioa_state != PMC_DEVICE_EVENT_RESET_START &&
	    pinstance->scn.ioa_state != PMC_DEVICE_EVENT_SHUTDOWN_START)
		pmcraid_notify_ioastate(pinstance,
					PMC_DEVICE_EVENT_RESET_START);

	pinstance->ioa_state = IOA_STATE_IN_RESET_ALERT;
	scsi_block_requests(pinstance->host);
	pmcraid_reset_alert(cmd);
	spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
}