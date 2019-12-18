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
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; int /*<<< orphan*/  nlp_listp; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLP_STE_UNUSED_NODE ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_cancel_retry_delay_tmo (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_counters (struct lpfc_vport*,scalar_t__,int) ; 
 int /*<<< orphan*/  lpfc_nlp_state_cleanup (struct lpfc_vport*,struct lpfc_nodelist*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_dequeue_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);

	lpfc_cancel_retry_delay_tmo(vport, ndlp);
	if (ndlp->nlp_state && !list_empty(&ndlp->nlp_listp))
		lpfc_nlp_counters(vport, ndlp->nlp_state, -1);
	spin_lock_irq(shost->host_lock);
	list_del_init(&ndlp->nlp_listp);
	spin_unlock_irq(shost->host_lock);
	lpfc_nlp_state_cleanup(vport, ndlp, ndlp->nlp_state,
				NLP_STE_UNUSED_NODE);
}