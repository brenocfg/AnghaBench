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
struct pmcraid_instance {int force_ioa_reset; struct pmcraid_cmd* reset_cmd; int /*<<< orphan*/  ioa_shutdown_type; int /*<<< orphan*/  host; int /*<<< orphan*/  ioa_reset_in_progress; } ;
struct pmcraid_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_DEVICE_EVENT_RESET_START ; 
 int /*<<< orphan*/  SHUTDOWN_NONE ; 
 int /*<<< orphan*/  pmcraid_err (char*) ; 
 struct pmcraid_cmd* pmcraid_get_free_cmd (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_ioa_reset (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_notify_ioastate (struct pmcraid_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmcraid_initiate_reset(struct pmcraid_instance *pinstance)
{
	struct pmcraid_cmd *cmd;

	/* If the reset is already in progress, just return, otherwise start
	 * reset sequence and return
	 */
	if (!pinstance->ioa_reset_in_progress) {
		scsi_block_requests(pinstance->host);
		cmd = pmcraid_get_free_cmd(pinstance);

		if (cmd == NULL) {
			pmcraid_err("no cmnd blocks for initiate_reset\n");
			return;
		}

		pinstance->ioa_shutdown_type = SHUTDOWN_NONE;
		pinstance->reset_cmd = cmd;
		pinstance->force_ioa_reset = 1;
		pmcraid_notify_ioastate(pinstance,
					PMC_DEVICE_EVENT_RESET_START);
		pmcraid_ioa_reset(cmd);
	}
}