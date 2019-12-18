#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fcf_flag; } ;
struct lpfc_hba {int hba_flag; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  hbalock; TYPE_7__* pport; TYPE_1__ fcf; } ;
struct TYPE_10__ {scalar_t__ port_state; int fc_flag; } ;
struct TYPE_9__ {int /*<<< orphan*/  mbox_cmpl; TYPE_7__* vport; } ;
typedef  TYPE_2__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FCF_AVAILABLE ; 
 int FCF_IN_USE ; 
 int FCF_REGISTERED ; 
 int FCF_RR_INPROG ; 
 int FCF_SCAN_DONE ; 
 int FCF_TS_INPROG ; 
 int FC_FABRIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LPFC_FLOGI ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  lpfc_initial_flogi (TYPE_7__*) ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_reg_fcfi ; 
 int /*<<< orphan*/  lpfc_reg_fcfi (struct lpfc_hba*,TYPE_2__*) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_register_fcf(struct lpfc_hba *phba)
{
	LPFC_MBOXQ_t *fcf_mbxq;
	int rc;

	spin_lock_irq(&phba->hbalock);
	/* If the FCF is not available do nothing. */
	if (!(phba->fcf.fcf_flag & FCF_AVAILABLE)) {
		phba->hba_flag &= ~(FCF_TS_INPROG | FCF_RR_INPROG);
		spin_unlock_irq(&phba->hbalock);
		return;
	}

	/* The FCF is already registered, start discovery */
	if (phba->fcf.fcf_flag & FCF_REGISTERED) {
		phba->fcf.fcf_flag |= (FCF_SCAN_DONE | FCF_IN_USE);
		phba->hba_flag &= ~FCF_TS_INPROG;
		if (phba->pport->port_state != LPFC_FLOGI &&
		    phba->pport->fc_flag & FC_FABRIC) {
			phba->hba_flag |= FCF_RR_INPROG;
			spin_unlock_irq(&phba->hbalock);
			lpfc_initial_flogi(phba->pport);
			return;
		}
		spin_unlock_irq(&phba->hbalock);
		return;
	}
	spin_unlock_irq(&phba->hbalock);

	fcf_mbxq = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!fcf_mbxq) {
		spin_lock_irq(&phba->hbalock);
		phba->hba_flag &= ~(FCF_TS_INPROG | FCF_RR_INPROG);
		spin_unlock_irq(&phba->hbalock);
		return;
	}

	lpfc_reg_fcfi(phba, fcf_mbxq);
	fcf_mbxq->vport = phba->pport;
	fcf_mbxq->mbox_cmpl = lpfc_mbx_cmpl_reg_fcfi;
	rc = lpfc_sli_issue_mbox(phba, fcf_mbxq, MBX_NOWAIT);
	if (rc == MBX_NOT_FINISHED) {
		spin_lock_irq(&phba->hbalock);
		phba->hba_flag &= ~(FCF_TS_INPROG | FCF_RR_INPROG);
		spin_unlock_irq(&phba->hbalock);
		mempool_free(fcf_mbxq, phba->mbox_mem_pool);
	}

	return;
}