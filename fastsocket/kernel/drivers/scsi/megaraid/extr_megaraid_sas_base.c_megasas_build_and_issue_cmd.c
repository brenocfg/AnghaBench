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
typedef  int u32 ;
struct TYPE_3__ {char* ptr; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct megasas_instance {int /*<<< orphan*/  reg_set; TYPE_2__* instancet; int /*<<< orphan*/  fw_outstanding; } ;
struct megasas_cmd {scalar_t__ frame_count; int /*<<< orphan*/  frame_phys_addr; struct scsi_cmnd* scmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fire_cmd ) (struct megasas_instance*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int megasas_build_dcdb (struct megasas_instance*,struct scsi_cmnd*,struct megasas_cmd*) ; 
 int megasas_build_ldio (struct megasas_instance*,struct scsi_cmnd*,struct megasas_cmd*) ; 
 struct megasas_cmd* megasas_get_cmd (struct megasas_instance*) ; 
 scalar_t__ megasas_is_ldio (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  megasas_return_cmd (struct megasas_instance*,struct megasas_cmd*) ; 
 int /*<<< orphan*/  stub1 (struct megasas_instance*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

u32
megasas_build_and_issue_cmd(struct megasas_instance *instance,
			    struct scsi_cmnd *scmd)
{
	struct megasas_cmd *cmd;
	u32 frame_count;

	cmd = megasas_get_cmd(instance);
	if (!cmd)
		return SCSI_MLQUEUE_HOST_BUSY;

	/*
	 * Logical drive command
	 */
	if (megasas_is_ldio(scmd))
		frame_count = megasas_build_ldio(instance, scmd, cmd);
	else
		frame_count = megasas_build_dcdb(instance, scmd, cmd);

	if (!frame_count)
		goto out_return_cmd;

	cmd->scmd = scmd;
	scmd->SCp.ptr = (char *)cmd;

	/*
	 * Issue the command to the FW
	 */
	atomic_inc(&instance->fw_outstanding);

	instance->instancet->fire_cmd(instance, cmd->frame_phys_addr,
				cmd->frame_count-1, instance->reg_set);

	return 0;
out_return_cmd:
	megasas_return_cmd(instance, cmd);
	return 1;
}