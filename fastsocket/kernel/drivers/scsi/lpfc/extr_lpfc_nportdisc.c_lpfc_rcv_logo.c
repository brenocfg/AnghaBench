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
typedef  scalar_t__ uint32_t ;
struct lpfc_vport {scalar_t__ port_state; int fc_flag; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {scalar_t__ nlp_DID; int nlp_type; scalar_t__ nlp_state; scalar_t__ nlp_prev_state; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_last_elscmd; int /*<<< orphan*/  nlp_delayfunc; } ;
struct lpfc_iocbq {int dummy; } ;
struct lpfc_hba {int max_vports; TYPE_1__* pport; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  fc_flag; } ;

/* Variables and functions */
 scalar_t__ ELS_CMD_ACC ; 
 int /*<<< orphan*/  ELS_CMD_FDISC ; 
 int /*<<< orphan*/  ELS_CMD_PLOGI ; 
 scalar_t__ ELS_CMD_PRLO ; 
 int /*<<< orphan*/  FC_LOGO_RCVD_DID_CHNG ; 
 int FC_VPORT_LOGO_RCVD ; 
 scalar_t__ Fabric_DID ; 
 scalar_t__ LPFC_FDISC ; 
 int /*<<< orphan*/  NLP_DELAY_TMO ; 
 int NLP_FABRIC ; 
 int NLP_FCP_INITIATOR ; 
 int NLP_FCP_TARGET ; 
 int /*<<< orphan*/  NLP_LOGO_ACC ; 
 int /*<<< orphan*/  NLP_NPR_ADISC ; 
 scalar_t__ NLP_STE_ADISC_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 scalar_t__ jiffies ; 
 struct lpfc_vport** lpfc_create_vport_work_array (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_destroy_vport_work_array (struct lpfc_hba*,struct lpfc_vport**) ; 
 int /*<<< orphan*/  lpfc_els_rsp_acc (struct lpfc_vport*,scalar_t__,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_linkdown_port (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_retry_pport_discovery (struct lpfc_hba*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_rcv_logo(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
	      struct lpfc_iocbq *cmdiocb, uint32_t els_cmd)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba    *phba = vport->phba;
	struct lpfc_vport **vports;
	int i, active_vlink_present = 0 ;

	/* Put ndlp in NPR state with 1 sec timeout for plogi, ACC logo */
	/* Only call LOGO ACC for first LOGO, this avoids sending unnecessary
	 * PLOGIs during LOGO storms from a device.
	 */
	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag |= NLP_LOGO_ACC;
	spin_unlock_irq(shost->host_lock);
	if (els_cmd == ELS_CMD_PRLO)
		lpfc_els_rsp_acc(vport, ELS_CMD_PRLO, cmdiocb, ndlp, NULL);
	else
		lpfc_els_rsp_acc(vport, ELS_CMD_ACC, cmdiocb, ndlp, NULL);
	if (ndlp->nlp_DID == Fabric_DID) {
		if (vport->port_state <= LPFC_FDISC)
			goto out;
		lpfc_linkdown_port(vport);
		spin_lock_irq(shost->host_lock);
		vport->fc_flag |= FC_VPORT_LOGO_RCVD;
		spin_unlock_irq(shost->host_lock);
		vports = lpfc_create_vport_work_array(phba);
		if (vports) {
			for (i = 0; i <= phba->max_vports && vports[i] != NULL;
					i++) {
				if ((!(vports[i]->fc_flag &
					FC_VPORT_LOGO_RCVD)) &&
					(vports[i]->port_state > LPFC_FDISC)) {
					active_vlink_present = 1;
					break;
				}
			}
			lpfc_destroy_vport_work_array(phba, vports);
		}

		if (active_vlink_present) {
			/*
			 * If there are other active VLinks present,
			 * re-instantiate the Vlink using FDISC.
			 */
			mod_timer(&ndlp->nlp_delayfunc,
				  jiffies + msecs_to_jiffies(1000));
			spin_lock_irq(shost->host_lock);
			ndlp->nlp_flag |= NLP_DELAY_TMO;
			spin_unlock_irq(shost->host_lock);
			ndlp->nlp_last_elscmd = ELS_CMD_FDISC;
			vport->port_state = LPFC_FDISC;
		} else {
			spin_lock_irq(shost->host_lock);
			phba->pport->fc_flag &= ~FC_LOGO_RCVD_DID_CHNG;
			spin_unlock_irq(shost->host_lock);
			lpfc_retry_pport_discovery(phba);
		}
	} else if ((!(ndlp->nlp_type & NLP_FABRIC) &&
		((ndlp->nlp_type & NLP_FCP_TARGET) ||
		!(ndlp->nlp_type & NLP_FCP_INITIATOR))) ||
		(ndlp->nlp_state == NLP_STE_ADISC_ISSUE)) {
		/* Only try to re-login if this is NOT a Fabric Node */
		mod_timer(&ndlp->nlp_delayfunc,
			  jiffies + msecs_to_jiffies(1000 * 1));
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag |= NLP_DELAY_TMO;
		spin_unlock_irq(shost->host_lock);

		ndlp->nlp_last_elscmd = ELS_CMD_PLOGI;
	}
out:
	ndlp->nlp_prev_state = ndlp->nlp_state;
	lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);

	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag &= ~NLP_NPR_ADISC;
	spin_unlock_irq(shost->host_lock);
	/* The driver has to wait until the ACC completes before it continues
	 * processing the LOGO.  The action will resume in
	 * lpfc_cmpl_els_logo_acc routine. Since part of processing includes an
	 * unreg_login, the driver waits so the ACC does not get aborted.
	 */
	return 0;
}