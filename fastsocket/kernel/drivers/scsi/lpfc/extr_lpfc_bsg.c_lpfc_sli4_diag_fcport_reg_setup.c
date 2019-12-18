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
struct TYPE_5__ {int /*<<< orphan*/ * vfi_ids; } ;
struct TYPE_4__ {int /*<<< orphan*/  fcfi; } ;
struct lpfc_hba {TYPE_3__* pport; int /*<<< orphan*/ * vpi_ids; TYPE_2__ sli4_hba; TYPE_1__ fcf; } ;
struct TYPE_6__ {int fc_flag; size_t vfi; size_t vpi; int /*<<< orphan*/  fc_myDID; } ;

/* Variables and functions */
 int EINVAL ; 
 int FC_VFI_REGISTERED ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_LIBDFC ; 
 int lpfc_issue_reg_vfi (TYPE_3__*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_sli4_diag_fcport_reg_setup(struct lpfc_hba *phba)
{
	int rc;

	if (phba->pport->fc_flag & FC_VFI_REGISTERED) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_LIBDFC,
				"3136 Port still had vfi registered: "
				"mydid:x%x, fcfi:%d, vfi:%d, vpi:%d\n",
				phba->pport->fc_myDID, phba->fcf.fcfi,
				phba->sli4_hba.vfi_ids[phba->pport->vfi],
				phba->vpi_ids[phba->pport->vpi]);
		return -EINVAL;
	}
	rc = lpfc_issue_reg_vfi(phba->pport);
	return rc;
}