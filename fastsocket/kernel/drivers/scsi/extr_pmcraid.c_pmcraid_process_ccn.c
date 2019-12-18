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
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  ignore; int /*<<< orphan*/ * cmd; } ;
struct pmcraid_instance {TYPE_3__* host; TYPE_2__* pdev; TYPE_1__ ccn; } ;
struct pmcraid_cmd {TYPE_4__* ioa_cb; struct pmcraid_instance* drv_inst; } ;
struct TYPE_10__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_9__ {TYPE_5__ ioasa; } ;
struct TYPE_8__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCRAID_HCAM_CODE_CONFIG_CHANGE ; 
 scalar_t__ PMCRAID_IOASC_IOA_WAS_RESET ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_handle_config_change (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_return_cmd (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_send_hcam (struct pmcraid_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void pmcraid_process_ccn(struct pmcraid_cmd *cmd)
{
	struct pmcraid_instance *pinstance = cmd->drv_inst;
	u32 ioasc = le32_to_cpu(cmd->ioa_cb->ioasa.ioasc);
	unsigned long lock_flags;

	pinstance->ccn.cmd = NULL;
	pmcraid_return_cmd(cmd);

	/* If driver initiated IOA reset happened while this hcam was pending
	 * with IOA, or IOA bringdown sequence is in progress, no need to
	 * re-register the hcam
	 */
	if (ioasc == PMCRAID_IOASC_IOA_WAS_RESET ||
	    atomic_read(&pinstance->ccn.ignore) == 1) {
		return;
	} else if (ioasc) {
		dev_info(&pinstance->pdev->dev,
			"Host RCB (CCN) failed with IOASC: 0x%08X\n", ioasc);
		spin_lock_irqsave(pinstance->host->host_lock, lock_flags);
		pmcraid_send_hcam(pinstance, PMCRAID_HCAM_CODE_CONFIG_CHANGE);
		spin_unlock_irqrestore(pinstance->host->host_lock, lock_flags);
	} else {
		pmcraid_handle_config_change(pinstance);
	}
}