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
typedef  int uint32_t ;
struct TYPE_6__ {TYPE_2__* fcp_eq_hdl; } ;
struct lpfc_hba {scalar_t__ intr_type; int cfg_fcp_io_channel; TYPE_3__ sli4_hba; TYPE_1__* pcidev; } ;
struct TYPE_5__ {int idx; int /*<<< orphan*/  fcp_eq_in_use; struct lpfc_hba* phba; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ INTx ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  LPFC_DRIVER_NAME ; 
 int LPFC_INTR_ERROR ; 
 scalar_t__ MSI ; 
 scalar_t__ MSIX ; 
 scalar_t__ NONE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int lpfc_sli4_enable_msi (struct lpfc_hba*) ; 
 int lpfc_sli4_enable_msix (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_intr_handler ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpfc_hba*) ; 

__attribute__((used)) static uint32_t
lpfc_sli4_enable_intr(struct lpfc_hba *phba, uint32_t cfg_mode)
{
	uint32_t intr_mode = LPFC_INTR_ERROR;
	int retval, index;

	if (cfg_mode == 2) {
		/* Preparation before conf_msi mbox cmd */
		retval = 0;
		if (!retval) {
			/* Now, try to enable MSI-X interrupt mode */
			retval = lpfc_sli4_enable_msix(phba);
			if (!retval) {
				/* Indicate initialization to MSI-X mode */
				phba->intr_type = MSIX;
				intr_mode = 2;
			}
		}
	}

	/* Fallback to MSI if MSI-X initialization failed */
	if (cfg_mode >= 1 && phba->intr_type == NONE) {
		retval = lpfc_sli4_enable_msi(phba);
		if (!retval) {
			/* Indicate initialization to MSI mode */
			phba->intr_type = MSI;
			intr_mode = 1;
		}
	}

	/* Fallback to INTx if both MSI-X/MSI initalization failed */
	if (phba->intr_type == NONE) {
		retval = request_irq(phba->pcidev->irq, lpfc_sli4_intr_handler,
				     IRQF_SHARED, LPFC_DRIVER_NAME, phba);
		if (!retval) {
			/* Indicate initialization to INTx mode */
			phba->intr_type = INTx;
			intr_mode = 0;
			for (index = 0; index < phba->cfg_fcp_io_channel;
			     index++) {
				phba->sli4_hba.fcp_eq_hdl[index].idx = index;
				phba->sli4_hba.fcp_eq_hdl[index].phba = phba;
				atomic_set(&phba->sli4_hba.fcp_eq_hdl[index].
					fcp_eq_in_use, 1);
			}
		}
	}
	return intr_mode;
}