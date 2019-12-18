#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {scalar_t__ port_state; scalar_t__ fc_ns_retry; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_type; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_rpi; } ;
struct lpfc_hba {scalar_t__ fc_topology; scalar_t__ sli_rev; int /*<<< orphan*/  mbox_mem_pool; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct TYPE_8__ {int /*<<< orphan*/ * varWords; } ;
struct TYPE_9__ {TYPE_2__ un; scalar_t__ mbxStatus; } ;
struct TYPE_7__ {TYPE_3__ mb; } ;
struct TYPE_10__ {int /*<<< orphan*/ * context2; int /*<<< orphan*/ * context1; struct lpfc_vport* vport; TYPE_1__ u; } ;
typedef  TYPE_3__ MAILBOX_t ;
typedef  TYPE_4__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_ELS ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 
 scalar_t__ LPFC_VPORT_READY ; 
 int /*<<< orphan*/  NLP_FABRIC ; 
 int /*<<< orphan*/  NLP_RPI_REGISTERED ; 
 int /*<<< orphan*/  NLP_STE_UNMAPPED_NODE ; 
 int /*<<< orphan*/  SCR_DID ; 
 int /*<<< orphan*/  SLI_CTNS_GID_FT ; 
 int /*<<< orphan*/  SLI_CTNS_RFF_ID ; 
 int /*<<< orphan*/  SLI_CTNS_RFT_ID ; 
 int /*<<< orphan*/  SLI_CTNS_RNN_ID ; 
 int /*<<< orphan*/  SLI_CTNS_RSNN_NN ; 
 int /*<<< orphan*/  SLI_CTNS_RSPN_ID ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 int /*<<< orphan*/  lpfc_disc_list_loopmap (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_disc_start (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_issue_els_scr (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_not_used (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_ns_cmd (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_4__*,int /*<<< orphan*/ ) ; 

void
lpfc_mbx_cmpl_ns_reg_login(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	MAILBOX_t *mb = &pmb->u.mb;
	struct lpfc_dmabuf *mp = (struct lpfc_dmabuf *) (pmb->context1);
	struct lpfc_nodelist *ndlp = (struct lpfc_nodelist *) pmb->context2;
	struct lpfc_vport *vport = pmb->vport;

	pmb->context1 = NULL;
	pmb->context2 = NULL;

	if (mb->mbxStatus) {
out:
		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
				 "0260 Register NameServer error: 0x%x\n",
				 mb->mbxStatus);
		/* decrement the node reference count held for this
		 * callback function.
		 */
		lpfc_nlp_put(ndlp);
		lpfc_mbuf_free(phba, mp->virt, mp->phys);
		kfree(mp);
		mempool_free(pmb, phba->mbox_mem_pool);

		/* If no other thread is using the ndlp, free it */
		lpfc_nlp_not_used(ndlp);

		if (phba->fc_topology == LPFC_TOPOLOGY_LOOP) {
			/*
			 * RegLogin failed, use loop map to make discovery
			 * list
			 */
			lpfc_disc_list_loopmap(vport);

			/* Start discovery */
			lpfc_disc_start(vport);
			return;
		}
		lpfc_vport_set_state(vport, FC_VPORT_FAILED);
		return;
	}

	if (phba->sli_rev < LPFC_SLI_REV4)
		ndlp->nlp_rpi = mb->un.varWords[0];
	ndlp->nlp_flag |= NLP_RPI_REGISTERED;
	ndlp->nlp_type |= NLP_FABRIC;
	lpfc_nlp_set_state(vport, ndlp, NLP_STE_UNMAPPED_NODE);

	if (vport->port_state < LPFC_VPORT_READY) {
		/* Link up discovery requires Fabric registration. */
		lpfc_ns_cmd(vport, SLI_CTNS_RFF_ID, 0, 0); /* Do this first! */
		lpfc_ns_cmd(vport, SLI_CTNS_RNN_ID, 0, 0);
		lpfc_ns_cmd(vport, SLI_CTNS_RSNN_NN, 0, 0);
		lpfc_ns_cmd(vport, SLI_CTNS_RSPN_ID, 0, 0);
		lpfc_ns_cmd(vport, SLI_CTNS_RFT_ID, 0, 0);

		/* Issue SCR just before NameServer GID_FT Query */
		lpfc_issue_els_scr(vport, SCR_DID, 0);
	}

	vport->fc_ns_retry = 0;
	/* Good status, issue CT Request to NameServer */
	if (lpfc_ns_cmd(vport, SLI_CTNS_GID_FT, 0, 0)) {
		/* Cannot issue NameServer Query, so finish up discovery */
		goto out;
	}

	/* decrement the node reference count held for this
	 * callback function.
	 */
	lpfc_nlp_put(ndlp);
	lpfc_mbuf_free(phba, mp->virt, mp->phys);
	kfree(mp);
	mempool_free(pmb, phba->mbox_mem_pool);

	return;
}