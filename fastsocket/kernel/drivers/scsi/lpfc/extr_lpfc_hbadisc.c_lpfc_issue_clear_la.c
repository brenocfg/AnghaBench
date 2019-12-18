#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {scalar_t__ port_type; } ;
struct lpfc_sli_ring {int /*<<< orphan*/  flag; } ;
struct lpfc_sli {size_t extra_ring; size_t fcp_ring; size_t next_ring; struct lpfc_sli_ring* ring; } ;
struct lpfc_hba {scalar_t__ link_state; scalar_t__ sli_rev; int /*<<< orphan*/  mbox_mem_pool; struct lpfc_sli sli; } ;
struct TYPE_6__ {struct lpfc_vport* vport; int /*<<< orphan*/  mbox_cmpl; } ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LPFC_CLEAR_LA ; 
 scalar_t__ LPFC_HBA_ERROR ; 
 scalar_t__ LPFC_PHYSICAL_PORT ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  LPFC_STOP_IOCB_EVENT ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  lpfc_clear_la (struct lpfc_hba*,TYPE_1__*) ; 
 int /*<<< orphan*/  lpfc_disc_flush_list (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_clear_la ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
lpfc_issue_clear_la(struct lpfc_hba *phba, struct lpfc_vport *vport)
{
	LPFC_MBOXQ_t *mbox;
	struct lpfc_sli *psli = &phba->sli;
	struct lpfc_sli_ring *extra_ring = &psli->ring[psli->extra_ring];
	struct lpfc_sli_ring *fcp_ring   = &psli->ring[psli->fcp_ring];
	struct lpfc_sli_ring *next_ring  = &psli->ring[psli->next_ring];
	int  rc;

	/*
	 * if it's not a physical port or if we already send
	 * clear_la then don't send it.
	 */
	if ((phba->link_state >= LPFC_CLEAR_LA) ||
	    (vport->port_type != LPFC_PHYSICAL_PORT) ||
		(phba->sli_rev == LPFC_SLI_REV4))
		return;

			/* Link up discovery */
	if ((mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL)) != NULL) {
		phba->link_state = LPFC_CLEAR_LA;
		lpfc_clear_la(phba, mbox);
		mbox->mbox_cmpl = lpfc_mbx_cmpl_clear_la;
		mbox->vport = vport;
		rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
		if (rc == MBX_NOT_FINISHED) {
			mempool_free(mbox, phba->mbox_mem_pool);
			lpfc_disc_flush_list(vport);
			extra_ring->flag &= ~LPFC_STOP_IOCB_EVENT;
			fcp_ring->flag &= ~LPFC_STOP_IOCB_EVENT;
			next_ring->flag &= ~LPFC_STOP_IOCB_EVENT;
			phba->link_state = LPFC_HBA_ERROR;
		}
	}
}