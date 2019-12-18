#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct sbp2_lu {int /*<<< orphan*/  cmd_orb_lock; } ;
struct sbp2_command_info {TYPE_3__* Current_SCpnt; int /*<<< orphan*/  (* Current_done ) (TYPE_3__*) ;} ;
struct TYPE_6__ {int result; } ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int /*<<< orphan*/  DID_BUS_BUSY ; 
 int /*<<< orphan*/  SBP2_INFO (char*) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  sbp2_agent_reset (struct sbp2_lu*,int) ; 
 int /*<<< orphan*/  sbp2scsi_complete_all_commands (struct sbp2_lu*,int /*<<< orphan*/ ) ; 
 struct sbp2_command_info* sbp2util_find_command_for_SCpnt (struct sbp2_lu*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sbp2util_mark_command_completed (struct sbp2_lu*,struct sbp2_command_info*) ; 
 scalar_t__ sbp2util_node_is_available (struct sbp2_lu*) ; 
 int /*<<< orphan*/  scsi_print_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static int sbp2scsi_abort(struct scsi_cmnd *SCpnt)
{
	struct sbp2_lu *lu = (struct sbp2_lu *)SCpnt->device->host->hostdata[0];
	struct sbp2_command_info *cmd;
	unsigned long flags;

	SBP2_INFO("aborting sbp2 command");
	scsi_print_command(SCpnt);

	if (sbp2util_node_is_available(lu)) {
		sbp2_agent_reset(lu, 1);

		/* Return a matching command structure to the free pool. */
		spin_lock_irqsave(&lu->cmd_orb_lock, flags);
		cmd = sbp2util_find_command_for_SCpnt(lu, SCpnt);
		if (cmd) {
			sbp2util_mark_command_completed(lu, cmd);
			if (cmd->Current_SCpnt) {
				cmd->Current_SCpnt->result = DID_ABORT << 16;
				cmd->Current_done(cmd->Current_SCpnt);
			}
		}
		spin_unlock_irqrestore(&lu->cmd_orb_lock, flags);

		sbp2scsi_complete_all_commands(lu, DID_BUS_BUSY);
	}

	return SUCCESS;
}