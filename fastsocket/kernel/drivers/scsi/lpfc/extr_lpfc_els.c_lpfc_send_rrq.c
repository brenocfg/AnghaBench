#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lpfc_nodelist {int dummy; } ;
struct lpfc_node_rrq {int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  vport; int /*<<< orphan*/  xritag; } ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 struct lpfc_nodelist* lpfc_findnode_did (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lpfc_issue_els_rrq (int /*<<< orphan*/ ,struct lpfc_nodelist*,int /*<<< orphan*/ ,struct lpfc_node_rrq*) ; 
 scalar_t__ lpfc_test_rrq_active (struct lpfc_hba*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 

int
lpfc_send_rrq(struct lpfc_hba *phba, struct lpfc_node_rrq *rrq)
{
	struct lpfc_nodelist *ndlp = lpfc_findnode_did(rrq->vport,
							rrq->nlp_DID);
	if (lpfc_test_rrq_active(phba, ndlp, rrq->xritag))
		return lpfc_issue_els_rrq(rrq->vport, ndlp,
					 rrq->nlp_DID, rrq);
	else
		return 1;
}