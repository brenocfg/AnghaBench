#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {TYPE_1__* hcam; } ;
struct pmcraid_instance {int /*<<< orphan*/  host; TYPE_3__* pdev; TYPE_2__ ldn; } ;
struct TYPE_8__ {int /*<<< orphan*/  fd_ra; int /*<<< orphan*/  fd_ioasc; } ;
struct pmcraid_hcam_ldn {TYPE_4__ error_log; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ notification_type; scalar_t__ notification_lost; int /*<<< orphan*/  overlay_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  op_code; int /*<<< orphan*/  ilid; } ;

/* Variables and functions */
 scalar_t__ HOSTRCB_NOTIFICATIONS_LOST ; 
 scalar_t__ NOTIFICATION_TYPE_ERROR_LOG ; 
 scalar_t__ PMCRAID_IOASC_UA_BUS_WAS_RESET ; 
 scalar_t__ PMCRAID_IOASC_UA_BUS_WAS_RESET_BY_OTHER ; 
 int /*<<< orphan*/  RES_BUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_report_bus_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmcraid_handle_error_log(struct pmcraid_instance *pinstance)
{
	struct pmcraid_hcam_ldn *hcam_ldn;
	u32 ioasc;

	hcam_ldn = (struct pmcraid_hcam_ldn *)pinstance->ldn.hcam;

	pmcraid_info
		("LDN(%x): %x type: %x lost: %x flags: %x overlay id: %x\n",
		 pinstance->ldn.hcam->ilid,
		 pinstance->ldn.hcam->op_code,
		 pinstance->ldn.hcam->notification_type,
		 pinstance->ldn.hcam->notification_lost,
		 pinstance->ldn.hcam->flags,
		 pinstance->ldn.hcam->overlay_id);

	/* log only the errors, no need to log informational log entries */
	if (pinstance->ldn.hcam->notification_type !=
	    NOTIFICATION_TYPE_ERROR_LOG)
		return;

	if (pinstance->ldn.hcam->notification_lost ==
	    HOSTRCB_NOTIFICATIONS_LOST)
		dev_info(&pinstance->pdev->dev, "Error notifications lost\n");

	ioasc = le32_to_cpu(hcam_ldn->error_log.fd_ioasc);

	if (ioasc == PMCRAID_IOASC_UA_BUS_WAS_RESET ||
		ioasc == PMCRAID_IOASC_UA_BUS_WAS_RESET_BY_OTHER) {
		dev_info(&pinstance->pdev->dev,
			"UnitAttention due to IOA Bus Reset\n");
		scsi_report_bus_reset(
			pinstance->host,
			RES_BUS(hcam_ldn->error_log.fd_ra));
	}

	return;
}