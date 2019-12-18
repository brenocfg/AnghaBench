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
struct lpfc_vport {TYPE_1__* phba; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; } ;
struct TYPE_2__ {scalar_t__ sli_rev; } ;

/* Variables and functions */
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ NLP_STE_UNUSED_NODE ; 
 int /*<<< orphan*/  lpfc_cleanup_vports_rrqs (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,scalar_t__) ; 

void
lpfc_drop_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp)
{
	/*
	 * Use of lpfc_drop_node and UNUSED list: lpfc_drop_node should
	 * be used if we wish to issue the "last" lpfc_nlp_put() to remove
	 * the ndlp from the vport. The ndlp marked as UNUSED on the list
	 * until ALL other outstanding threads have completed. We check
	 * that the ndlp not already in the UNUSED state before we proceed.
	 */
	if (ndlp->nlp_state == NLP_STE_UNUSED_NODE)
		return;
	lpfc_nlp_set_state(vport, ndlp, NLP_STE_UNUSED_NODE);
	if (vport->phba->sli_rev == LPFC_SLI_REV4)
		lpfc_cleanup_vports_rrqs(vport, ndlp);
	lpfc_nlp_put(ndlp);
	return;
}