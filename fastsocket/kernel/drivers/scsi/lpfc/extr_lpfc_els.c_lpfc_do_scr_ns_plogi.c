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
struct lpfc_vport {int fc_flag; scalar_t__ cfg_fdmi_on; int /*<<< orphan*/  delayed_disc_tmo; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  nlp_type; } ;
struct lpfc_hba {int fc_ratov; scalar_t__ fc_topology; int /*<<< orphan*/  nlp_mem_pool; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int FC_DISC_DELAYED ; 
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int /*<<< orphan*/  FDMI_DID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  LOG_ELS ; 
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_FABRIC ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 int /*<<< orphan*/  NLP_STE_PLOGI_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_UNUSED_NODE ; 
 int /*<<< orphan*/  NameServer_DID ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lpfc_disc_start (struct lpfc_vport*) ; 
 struct lpfc_nodelist* lpfc_enable_node (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_issue_els_plogi (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_init (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void
lpfc_do_scr_ns_plogi(struct lpfc_hba *phba, struct lpfc_vport *vport)
{
	struct lpfc_nodelist *ndlp, *ndlp_fdmi;
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);

	/*
	 * If lpfc_delay_discovery parameter is set and the clean address
	 * bit is cleared and fc fabric parameters chenged, delay FC NPort
	 * discovery.
	 */
	spin_lock_irq(shost->host_lock);
	if (vport->fc_flag & FC_DISC_DELAYED) {
		spin_unlock_irq(shost->host_lock);
		lpfc_printf_log(phba, KERN_ERR, LOG_DISCOVERY,
				"3334 Delay fc port discovery for %d seconds\n",
				phba->fc_ratov);
		mod_timer(&vport->delayed_disc_tmo,
			jiffies + msecs_to_jiffies(1000 * phba->fc_ratov));
		return;
	}
	spin_unlock_irq(shost->host_lock);

	ndlp = lpfc_findnode_did(vport, NameServer_DID);
	if (!ndlp) {
		ndlp = mempool_alloc(phba->nlp_mem_pool, GFP_KERNEL);
		if (!ndlp) {
			if (phba->fc_topology == LPFC_TOPOLOGY_LOOP) {
				lpfc_disc_start(vport);
				return;
			}
			lpfc_vport_set_state(vport, FC_VPORT_FAILED);
			lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
					 "0251 NameServer login: no memory\n");
			return;
		}
		lpfc_nlp_init(vport, ndlp, NameServer_DID);
	} else if (!NLP_CHK_NODE_ACT(ndlp)) {
		ndlp = lpfc_enable_node(vport, ndlp, NLP_STE_UNUSED_NODE);
		if (!ndlp) {
			if (phba->fc_topology == LPFC_TOPOLOGY_LOOP) {
				lpfc_disc_start(vport);
				return;
			}
			lpfc_vport_set_state(vport, FC_VPORT_FAILED);
			lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
					"0348 NameServer login: node freed\n");
			return;
		}
	}
	ndlp->nlp_type |= NLP_FABRIC;

	lpfc_nlp_set_state(vport, ndlp, NLP_STE_PLOGI_ISSUE);

	if (lpfc_issue_els_plogi(vport, ndlp->nlp_DID, 0)) {
		lpfc_vport_set_state(vport, FC_VPORT_FAILED);
		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
				 "0252 Cannot issue NameServer login\n");
		return;
	}

	if (vport->cfg_fdmi_on) {
		/* If this is the first time, allocate an ndlp and initialize
		 * it. Otherwise, make sure the node is enabled and then do the
		 * login.
		 */
		ndlp_fdmi = lpfc_findnode_did(vport, FDMI_DID);
		if (!ndlp_fdmi) {
			ndlp_fdmi = mempool_alloc(phba->nlp_mem_pool,
						  GFP_KERNEL);
			if (ndlp_fdmi) {
				lpfc_nlp_init(vport, ndlp_fdmi, FDMI_DID);
				ndlp_fdmi->nlp_type |= NLP_FABRIC;
			} else
				return;
		}
		if (!NLP_CHK_NODE_ACT(ndlp_fdmi))
			ndlp_fdmi = lpfc_enable_node(vport,
						     ndlp_fdmi,
						     NLP_STE_NPR_NODE);

		if (ndlp_fdmi) {
			lpfc_nlp_set_state(vport, ndlp_fdmi,
					   NLP_STE_PLOGI_ISSUE);
			lpfc_issue_els_plogi(vport, ndlp_fdmi->nlp_DID, 0);
		}
	}
}