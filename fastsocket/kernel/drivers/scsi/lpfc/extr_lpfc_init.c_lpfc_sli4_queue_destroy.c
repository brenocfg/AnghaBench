#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * mbx_cq; int /*<<< orphan*/ * els_cq; int /*<<< orphan*/ * dat_rq; int /*<<< orphan*/ * hdr_rq; int /*<<< orphan*/ * els_wq; int /*<<< orphan*/ * mbx_wq; int /*<<< orphan*/ ** fcp_cq_map; int /*<<< orphan*/ ** fcp_wq; int /*<<< orphan*/ ** fcp_cq; int /*<<< orphan*/ ** hba_eq; } ;
struct lpfc_hba {int cfg_fcp_io_channel; TYPE_1__ sli4_hba; int /*<<< orphan*/ * pci_bar4_memmap_p; int /*<<< orphan*/ * pci_bar2_memmap_p; int /*<<< orphan*/ * pci_bar0_memmap_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lpfc_sli4_queue_free (int /*<<< orphan*/ *) ; 

void
lpfc_sli4_queue_destroy(struct lpfc_hba *phba)
{
	int idx;

	if (phba->sli4_hba.hba_eq != NULL) {
		/* Release HBA event queue */
		for (idx = 0; idx < phba->cfg_fcp_io_channel; idx++) {
			if (phba->sli4_hba.hba_eq[idx] != NULL) {
				lpfc_sli4_queue_free(
					phba->sli4_hba.hba_eq[idx]);
				phba->sli4_hba.hba_eq[idx] = NULL;
			}
		}
		kfree(phba->sli4_hba.hba_eq);
		phba->sli4_hba.hba_eq = NULL;
	}

	if (phba->sli4_hba.fcp_cq != NULL) {
		/* Release FCP completion queue */
		for (idx = 0; idx < phba->cfg_fcp_io_channel; idx++) {
			if (phba->sli4_hba.fcp_cq[idx] != NULL) {
				lpfc_sli4_queue_free(
					phba->sli4_hba.fcp_cq[idx]);
				phba->sli4_hba.fcp_cq[idx] = NULL;
			}
		}
		kfree(phba->sli4_hba.fcp_cq);
		phba->sli4_hba.fcp_cq = NULL;
	}

	if (phba->sli4_hba.fcp_wq != NULL) {
		/* Release FCP work queue */
		for (idx = 0; idx < phba->cfg_fcp_io_channel; idx++) {
			if (phba->sli4_hba.fcp_wq[idx] != NULL) {
				lpfc_sli4_queue_free(
					phba->sli4_hba.fcp_wq[idx]);
				phba->sli4_hba.fcp_wq[idx] = NULL;
			}
		}
		kfree(phba->sli4_hba.fcp_wq);
		phba->sli4_hba.fcp_wq = NULL;
	}

	if (phba->pci_bar0_memmap_p) {
		iounmap(phba->pci_bar0_memmap_p);
		phba->pci_bar0_memmap_p = NULL;
	}
	if (phba->pci_bar2_memmap_p) {
		iounmap(phba->pci_bar2_memmap_p);
		phba->pci_bar2_memmap_p = NULL;
	}
	if (phba->pci_bar4_memmap_p) {
		iounmap(phba->pci_bar4_memmap_p);
		phba->pci_bar4_memmap_p = NULL;
	}

	/* Release FCP CQ mapping array */
	if (phba->sli4_hba.fcp_cq_map != NULL) {
		kfree(phba->sli4_hba.fcp_cq_map);
		phba->sli4_hba.fcp_cq_map = NULL;
	}

	/* Release mailbox command work queue */
	if (phba->sli4_hba.mbx_wq != NULL) {
		lpfc_sli4_queue_free(phba->sli4_hba.mbx_wq);
		phba->sli4_hba.mbx_wq = NULL;
	}

	/* Release ELS work queue */
	if (phba->sli4_hba.els_wq != NULL) {
		lpfc_sli4_queue_free(phba->sli4_hba.els_wq);
		phba->sli4_hba.els_wq = NULL;
	}

	/* Release unsolicited receive queue */
	if (phba->sli4_hba.hdr_rq != NULL) {
		lpfc_sli4_queue_free(phba->sli4_hba.hdr_rq);
		phba->sli4_hba.hdr_rq = NULL;
	}
	if (phba->sli4_hba.dat_rq != NULL) {
		lpfc_sli4_queue_free(phba->sli4_hba.dat_rq);
		phba->sli4_hba.dat_rq = NULL;
	}

	/* Release ELS complete queue */
	if (phba->sli4_hba.els_cq != NULL) {
		lpfc_sli4_queue_free(phba->sli4_hba.els_cq);
		phba->sli4_hba.els_cq = NULL;
	}

	/* Release mailbox command complete queue */
	if (phba->sli4_hba.mbx_cq != NULL) {
		lpfc_sli4_queue_free(phba->sli4_hba.mbx_cq);
		phba->sli4_hba.mbx_cq = NULL;
	}

	return;
}