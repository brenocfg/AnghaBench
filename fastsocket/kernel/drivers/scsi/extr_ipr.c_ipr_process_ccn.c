#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ipr_ioa_cfg {TYPE_3__* pdev; } ;
struct ipr_hostrcb {int /*<<< orphan*/  queue; } ;
struct TYPE_11__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_12__ {TYPE_5__ hdr; } ;
struct TYPE_7__ {TYPE_6__ ioasa; } ;
struct TYPE_10__ {struct ipr_hostrcb* hostrcb; } ;
struct ipr_cmnd {TYPE_2__* hrrq; int /*<<< orphan*/  queue; TYPE_1__ s; TYPE_4__ u; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  hrrq_free_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPR_HCAM_CDB_OP_CODE_CONFIG_CHANGE ; 
 scalar_t__ IPR_IOASC_IOA_WAS_RESET ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  ipr_handle_config_change (struct ipr_ioa_cfg*,struct ipr_hostrcb*) ; 
 int /*<<< orphan*/  ipr_send_hcam (struct ipr_ioa_cfg*,int /*<<< orphan*/ ,struct ipr_hostrcb*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipr_process_ccn(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	struct ipr_hostrcb *hostrcb = ipr_cmd->u.hostrcb;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	list_del(&hostrcb->queue);
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_free_q);

	if (ioasc) {
		if (ioasc != IPR_IOASC_IOA_WAS_RESET)
			dev_err(&ioa_cfg->pdev->dev,
				"Host RCB failed with IOASC: 0x%08X\n", ioasc);

		ipr_send_hcam(ioa_cfg, IPR_HCAM_CDB_OP_CODE_CONFIG_CHANGE, hostrcb);
	} else {
		ipr_handle_config_change(ioa_cfg, hostrcb);
	}
}