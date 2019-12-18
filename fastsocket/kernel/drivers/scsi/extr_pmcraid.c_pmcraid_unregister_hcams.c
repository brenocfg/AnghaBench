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
struct TYPE_4__ {int /*<<< orphan*/  ignore; } ;
struct TYPE_3__ {int /*<<< orphan*/  ignore; } ;
struct pmcraid_instance {int /*<<< orphan*/  ioa_state; scalar_t__ ioa_unit_check; scalar_t__ force_ioa_reset; int /*<<< orphan*/  ioa_bringdown; TYPE_2__ ldn; TYPE_1__ ccn; } ;
struct pmcraid_cmd {struct pmcraid_instance* drv_inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOA_STATE_IN_RESET_ALERT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmcraid_cancel_ldn (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_reset_alert (struct pmcraid_cmd*) ; 

__attribute__((used)) static void pmcraid_unregister_hcams(struct pmcraid_cmd *cmd)
{
	struct pmcraid_instance *pinstance = cmd->drv_inst;

	/* During IOA bringdown, HCAM gets fired and tasklet proceeds with
	 * handling hcam response though it is not necessary. In order to
	 * prevent this, set 'ignore', so that bring-down sequence doesn't
	 * re-send any more hcams
	 */
	atomic_set(&pinstance->ccn.ignore, 1);
	atomic_set(&pinstance->ldn.ignore, 1);

	/* If adapter reset was forced as part of runtime reset sequence,
	 * start the reset sequence. Reset will be triggered even in case
	 * IOA unit_check.
	 */
	if ((pinstance->force_ioa_reset && !pinstance->ioa_bringdown) ||
	     pinstance->ioa_unit_check) {
		pinstance->force_ioa_reset = 0;
		pinstance->ioa_unit_check = 0;
		pinstance->ioa_state = IOA_STATE_IN_RESET_ALERT;
		pmcraid_reset_alert(cmd);
		return;
	}

	/* Driver tries to cancel HCAMs by sending ABORT TASK for each HCAM
	 * one after the other. So CCN cancellation will be triggered by
	 * pmcraid_cancel_ldn itself.
	 */
	pmcraid_cancel_ldn(cmd);
}