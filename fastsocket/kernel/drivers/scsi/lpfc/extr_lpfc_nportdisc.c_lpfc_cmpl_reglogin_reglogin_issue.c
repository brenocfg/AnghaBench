#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {TYPE_3__* phba; int /*<<< orphan*/  port_state; } ;
struct lpfc_nodelist {int nlp_type; int /*<<< orphan*/  nlp_state; void* nlp_prev_state; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_rpi; int /*<<< orphan*/  nlp_last_elscmd; int /*<<< orphan*/  nlp_delayfunc; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  rpi; int /*<<< orphan*/  vpi; } ;
struct TYPE_10__ {int /*<<< orphan*/ * varWords; TYPE_2__ varRegLogin; } ;
struct TYPE_11__ {scalar_t__ mbxStatus; TYPE_4__ un; } ;
struct TYPE_7__ {TYPE_5__ mb; } ;
struct TYPE_12__ {TYPE_1__ u; } ;
struct TYPE_9__ {scalar_t__ sli_rev; } ;
typedef  TYPE_5__ MAILBOX_t ;
typedef  TYPE_6__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_PLOGI ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ MBXERR_RPI_FULL ; 
 int /*<<< orphan*/  NLP_DELAY_TMO ; 
 int NLP_FABRIC ; 
 int /*<<< orphan*/  NLP_RPI_REGISTERED ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 int /*<<< orphan*/  NLP_STE_PRLI_ISSUE ; 
 void* NLP_STE_REG_LOGIN_ISSUE ; 
 int /*<<< orphan*/  NLP_STE_UNMAPPED_NODE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lpfc_issue_els_logo (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_issue_els_prli (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_cmpl_reglogin_reglogin_issue(struct lpfc_vport *vport,
				  struct lpfc_nodelist *ndlp,
				  void *arg,
				  uint32_t evt)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	LPFC_MBOXQ_t *pmb = (LPFC_MBOXQ_t *) arg;
	MAILBOX_t *mb = &pmb->u.mb;
	uint32_t did  = mb->un.varWords[1];

	if (mb->mbxStatus) {
		/* RegLogin failed */
		lpfc_printf_vlog(vport, KERN_ERR, LOG_DISCOVERY,
				"0246 RegLogin failed Data: x%x x%x x%x x%x "
				 "x%x\n",
				 did, mb->mbxStatus, vport->port_state,
				 mb->un.varRegLogin.vpi,
				 mb->un.varRegLogin.rpi);
		/*
		 * If RegLogin failed due to lack of HBA resources do not
		 * retry discovery.
		 */
		if (mb->mbxStatus == MBXERR_RPI_FULL) {
			ndlp->nlp_prev_state = NLP_STE_REG_LOGIN_ISSUE;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
			return ndlp->nlp_state;
		}

		/* Put ndlp in npr state set plogi timer for 1 sec */
		mod_timer(&ndlp->nlp_delayfunc,
			  jiffies + msecs_to_jiffies(1000 * 1));
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag |= NLP_DELAY_TMO;
		spin_unlock_irq(shost->host_lock);
		ndlp->nlp_last_elscmd = ELS_CMD_PLOGI;

		lpfc_issue_els_logo(vport, ndlp, 0);
		ndlp->nlp_prev_state = NLP_STE_REG_LOGIN_ISSUE;
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
		return ndlp->nlp_state;
	}

	/* SLI4 ports have preallocated logical rpis. */
	if (vport->phba->sli_rev < LPFC_SLI_REV4)
		ndlp->nlp_rpi = mb->un.varWords[0];

	ndlp->nlp_flag |= NLP_RPI_REGISTERED;

	/* Only if we are not a fabric nport do we issue PRLI */
	if (!(ndlp->nlp_type & NLP_FABRIC)) {
		ndlp->nlp_prev_state = NLP_STE_REG_LOGIN_ISSUE;
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_PRLI_ISSUE);
		lpfc_issue_els_prli(vport, ndlp, 0);
	} else {
		ndlp->nlp_prev_state = NLP_STE_REG_LOGIN_ISSUE;
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_UNMAPPED_NODE);
	}
	return ndlp->nlp_state;
}