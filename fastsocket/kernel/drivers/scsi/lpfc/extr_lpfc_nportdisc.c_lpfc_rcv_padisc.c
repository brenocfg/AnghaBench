#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct serv_parm {int /*<<< orphan*/  portName; int /*<<< orphan*/  nodeName; } ;
struct TYPE_7__ {scalar_t__ vendorUnique; int /*<<< orphan*/  lsRjtRsnCodeExp; int /*<<< orphan*/  lsRjtRsnCode; scalar_t__ lsRjtRsvd0; } ;
struct TYPE_8__ {int /*<<< orphan*/  lsRjtError; TYPE_2__ b; } ;
struct ls_rjt {TYPE_3__ un; } ;
struct lpfc_vport {TYPE_1__* phba; } ;
struct lpfc_nodelist {int nlp_type; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_prev_state; int /*<<< orphan*/  nlp_last_elscmd; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_delayfunc; } ;
struct lpfc_name {int dummy; } ;
struct TYPE_9__ {scalar_t__ ulpStatus; } ;
struct lpfc_iocbq {scalar_t__ drvrTimeout; TYPE_4__ iocb; scalar_t__ context2; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_10__ {int /*<<< orphan*/  portName; int /*<<< orphan*/  nodeName; } ;
struct TYPE_6__ {scalar_t__ sli_rev; } ;
typedef  TYPE_4__ IOCB_t ;
typedef  TYPE_5__ ADISC ;

/* Variables and functions */
 scalar_t__ ELS_CMD_ADISC ; 
 int /*<<< orphan*/  ELS_CMD_PLOGI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  LSEXP_SPARM_OPTIONS ; 
 int /*<<< orphan*/  LSRJT_UNABLE_TPC ; 
 int /*<<< orphan*/  NLP_DELAY_TMO ; 
 int NLP_FCP_TARGET ; 
 int /*<<< orphan*/  NLP_STE_MAPPED_NODE ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 int /*<<< orphan*/  NLP_STE_UNMAPPED_NODE ; 
 scalar_t__ jiffies ; 
 struct lpfc_iocbq* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_check_adisc (struct lpfc_vport*,struct lpfc_nodelist*,struct lpfc_name*,struct lpfc_name*) ; 
 int /*<<< orphan*/  lpfc_els_rsp_acc (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_els_rsp_adisc_acc (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rsp_reject (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_resume_rpi ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_sli4_resume_rpi (struct lpfc_nodelist*,int /*<<< orphan*/ ,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_rcv_padisc(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
		struct lpfc_iocbq *cmdiocb)
{
	struct Scsi_Host   *shost = lpfc_shost_from_vport(vport);
	struct lpfc_iocbq  *elsiocb;
	struct lpfc_dmabuf *pcmd;
	struct serv_parm   *sp;
	struct lpfc_name   *pnn, *ppn;
	struct ls_rjt stat;
	ADISC *ap;
	IOCB_t *icmd;
	uint32_t *lp;
	uint32_t cmd;

	pcmd = (struct lpfc_dmabuf *) cmdiocb->context2;
	lp = (uint32_t *) pcmd->virt;

	cmd = *lp++;
	if (cmd == ELS_CMD_ADISC) {
		ap = (ADISC *) lp;
		pnn = (struct lpfc_name *) & ap->nodeName;
		ppn = (struct lpfc_name *) & ap->portName;
	} else {
		sp = (struct serv_parm *) lp;
		pnn = (struct lpfc_name *) & sp->nodeName;
		ppn = (struct lpfc_name *) & sp->portName;
	}

	icmd = &cmdiocb->iocb;
	if (icmd->ulpStatus == 0 && lpfc_check_adisc(vport, ndlp, pnn, ppn)) {

		/*
		 * As soon as  we send ACC, the remote NPort can
		 * start sending us data. Thus, for SLI4 we must
		 * resume the RPI before the ACC goes out.
		 */
		if (vport->phba->sli_rev == LPFC_SLI_REV4) {
			elsiocb = kmalloc(sizeof(struct lpfc_iocbq),
				GFP_KERNEL);
			if (elsiocb) {

				/* Save info from cmd IOCB used in rsp */
				memcpy((uint8_t *)elsiocb, (uint8_t *)cmdiocb,
					sizeof(struct lpfc_iocbq));

				/* Save the ELS cmd */
				elsiocb->drvrTimeout = cmd;

				lpfc_sli4_resume_rpi(ndlp,
					lpfc_mbx_cmpl_resume_rpi, elsiocb);
				goto out;
			}
		}

		if (cmd == ELS_CMD_ADISC) {
			lpfc_els_rsp_adisc_acc(vport, cmdiocb, ndlp);
		} else {
			lpfc_els_rsp_acc(vport, ELS_CMD_PLOGI, cmdiocb,
				ndlp, NULL);
		}
out:
		/* If we are authenticated, move to the proper state */
		if (ndlp->nlp_type & NLP_FCP_TARGET)
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_MAPPED_NODE);
		else
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_UNMAPPED_NODE);

		return 1;
	}
	/* Reject this request because invalid parameters */
	stat.un.b.lsRjtRsvd0 = 0;
	stat.un.b.lsRjtRsnCode = LSRJT_UNABLE_TPC;
	stat.un.b.lsRjtRsnCodeExp = LSEXP_SPARM_OPTIONS;
	stat.un.b.vendorUnique = 0;
	lpfc_els_rsp_reject(vport, stat.un.lsRjtError, cmdiocb, ndlp, NULL);

	/* 1 sec timeout */
	mod_timer(&ndlp->nlp_delayfunc, jiffies + msecs_to_jiffies(1000));

	spin_lock_irq(shost->host_lock);
	ndlp->nlp_flag |= NLP_DELAY_TMO;
	spin_unlock_irq(shost->host_lock);
	ndlp->nlp_last_elscmd = ELS_CMD_PLOGI;
	ndlp->nlp_prev_state = ndlp->nlp_state;
	lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
	return 0;
}