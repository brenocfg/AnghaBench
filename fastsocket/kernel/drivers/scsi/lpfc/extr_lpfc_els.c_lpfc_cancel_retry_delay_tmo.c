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
struct lpfc_work_evt {scalar_t__ evt_arg1; int /*<<< orphan*/  evt_listp; } ;
struct lpfc_vport {scalar_t__ num_disc_nodes; scalar_t__ port_state; int /*<<< orphan*/  fc_flag; } ;
struct lpfc_nodelist {int nlp_flag; struct lpfc_work_evt els_retry_evt; scalar_t__ nlp_last_elscmd; int /*<<< orphan*/  nlp_delayfunc; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_NDISC_ACTIVE ; 
 scalar_t__ LPFC_VPORT_READY ; 
 int NLP_DELAY_TMO ; 
 int NLP_NPR_2B_DISC ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_can_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_end_rscn (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_more_adisc (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_more_plogi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_cancel_retry_delay_tmo(struct lpfc_vport *vport, struct lpfc_nodelist *nlp)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_work_evt *evtp;

	if (!(nlp->nlp_flag & NLP_DELAY_TMO))
		return;
	spin_lock_irq(shost->host_lock);
	nlp->nlp_flag &= ~NLP_DELAY_TMO;
	spin_unlock_irq(shost->host_lock);
	del_timer_sync(&nlp->nlp_delayfunc);
	nlp->nlp_last_elscmd = 0;
	if (!list_empty(&nlp->els_retry_evt.evt_listp)) {
		list_del_init(&nlp->els_retry_evt.evt_listp);
		/* Decrement nlp reference count held for the delayed retry */
		evtp = &nlp->els_retry_evt;
		lpfc_nlp_put((struct lpfc_nodelist *)evtp->evt_arg1);
	}
	if (nlp->nlp_flag & NLP_NPR_2B_DISC) {
		spin_lock_irq(shost->host_lock);
		nlp->nlp_flag &= ~NLP_NPR_2B_DISC;
		spin_unlock_irq(shost->host_lock);
		if (vport->num_disc_nodes) {
			if (vport->port_state < LPFC_VPORT_READY) {
				/* Check if there are more ADISCs to be sent */
				lpfc_more_adisc(vport);
			} else {
				/* Check if there are more PLOGIs to be sent */
				lpfc_more_plogi(vport);
				if (vport->num_disc_nodes == 0) {
					spin_lock_irq(shost->host_lock);
					vport->fc_flag &= ~FC_NDISC_ACTIVE;
					spin_unlock_irq(shost->host_lock);
					lpfc_can_disctmo(vport);
					lpfc_end_rscn(vport);
				}
			}
		}
	}
	return;
}