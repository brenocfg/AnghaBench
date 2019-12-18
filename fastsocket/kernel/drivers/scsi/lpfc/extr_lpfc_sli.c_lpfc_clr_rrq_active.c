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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  xri_bitmap; } ;
struct lpfc_nodelist {TYPE_1__ active_rrqs; } ;
struct lpfc_node_rrq {scalar_t__ rrq_stop_time; scalar_t__ xritag; scalar_t__ send_rrq; struct lpfc_nodelist* ndlp; int /*<<< orphan*/  nlp_DID; scalar_t__ vport; } ;
struct lpfc_hba {int /*<<< orphan*/  rrq_pool; } ;

/* Variables and functions */
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 struct lpfc_nodelist* lpfc_findnode_did (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct lpfc_node_rrq*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
lpfc_clr_rrq_active(struct lpfc_hba *phba,
		    uint16_t xritag,
		    struct lpfc_node_rrq *rrq)
{
	struct lpfc_nodelist *ndlp = NULL;

	if ((rrq->vport) && NLP_CHK_NODE_ACT(rrq->ndlp))
		ndlp = lpfc_findnode_did(rrq->vport, rrq->nlp_DID);

	/* The target DID could have been swapped (cable swap)
	 * we should use the ndlp from the findnode if it is
	 * available.
	 */
	if ((!ndlp) && rrq->ndlp)
		ndlp = rrq->ndlp;

	if (!ndlp)
		goto out;

	if (test_and_clear_bit(xritag, ndlp->active_rrqs.xri_bitmap)) {
		rrq->send_rrq = 0;
		rrq->xritag = 0;
		rrq->rrq_stop_time = 0;
	}
out:
	mempool_free(rrq, phba->rrq_pool);
}