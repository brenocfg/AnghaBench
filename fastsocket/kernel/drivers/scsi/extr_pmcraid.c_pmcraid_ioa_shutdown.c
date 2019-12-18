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
struct pmcraid_cmd {int /*<<< orphan*/  drv_inst; TYPE_3__* ioa_cb; } ;
struct TYPE_5__ {int /*<<< orphan*/  response_handle; int /*<<< orphan*/ * cdb; int /*<<< orphan*/  resource_handle; int /*<<< orphan*/  request_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_6__ {TYPE_2__ ioarcb; TYPE_1__ ioasa; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCRAID_IOA_RES_HANDLE ; 
 int /*<<< orphan*/  PMCRAID_IOA_SHUTDOWN ; 
 int /*<<< orphan*/  PMCRAID_SHUTDOWN_NORMAL ; 
 int /*<<< orphan*/  PMCRAID_SHUTDOWN_TIMEOUT ; 
 int /*<<< orphan*/  PMC_DEVICE_EVENT_SHUTDOWN_START ; 
 int /*<<< orphan*/  REQ_TYPE_IOACMD ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pmcraid_ioa_shutdown_done ; 
 int /*<<< orphan*/  pmcraid_notify_ioastate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_reinit_cmdblk (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_send_cmd (struct pmcraid_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_timeout_handler ; 

__attribute__((used)) static void pmcraid_ioa_shutdown(struct pmcraid_cmd *cmd)
{
	pmcraid_info("response for Cancel CCN CDB[0] = %x ioasc = %x\n",
		     cmd->ioa_cb->ioarcb.cdb[0],
		     le32_to_cpu(cmd->ioa_cb->ioasa.ioasc));

	/* Note that commands sent during reset require next command to be sent
	 * to IOA. Hence reinit the done function as well as timeout function
	 */
	pmcraid_reinit_cmdblk(cmd);
	cmd->ioa_cb->ioarcb.request_type = REQ_TYPE_IOACMD;
	cmd->ioa_cb->ioarcb.resource_handle =
		cpu_to_le32(PMCRAID_IOA_RES_HANDLE);
	cmd->ioa_cb->ioarcb.cdb[0] = PMCRAID_IOA_SHUTDOWN;
	cmd->ioa_cb->ioarcb.cdb[1] = PMCRAID_SHUTDOWN_NORMAL;

	/* fire shutdown command to hardware. */
	pmcraid_info("firing normal shutdown command (%d) to IOA\n",
		     le32_to_cpu(cmd->ioa_cb->ioarcb.response_handle));

	pmcraid_notify_ioastate(cmd->drv_inst, PMC_DEVICE_EVENT_SHUTDOWN_START);

	pmcraid_send_cmd(cmd, pmcraid_ioa_shutdown_done,
			 PMCRAID_SHUTDOWN_TIMEOUT,
			 pmcraid_timeout_handler);
}