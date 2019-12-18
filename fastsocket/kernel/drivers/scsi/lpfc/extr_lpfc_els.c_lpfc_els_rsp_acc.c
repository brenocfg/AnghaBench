#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct serv_parm {int dummy; } ;
struct lpfc_vport {int /*<<< orphan*/  fc_flag; int /*<<< orphan*/  fc_sparam; struct lpfc_hba* phba; } ;
struct lpfc_sli {int dummy; } ;
struct lpfc_nodelist {int nlp_flag; int /*<<< orphan*/  nlp_rpi; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_DID; } ;
struct TYPE_10__ {int /*<<< orphan*/  ox_id; } ;
struct TYPE_11__ {TYPE_2__ rcvsli3; } ;
struct TYPE_15__ {int /*<<< orphan*/  ulpContext; TYPE_3__ unsli3; } ;
struct TYPE_9__ {int /*<<< orphan*/ * mbox; } ;
struct lpfc_iocbq {int /*<<< orphan*/  iocb_cmpl; TYPE_7__ iocb; int /*<<< orphan*/  iotag; scalar_t__ context2; int /*<<< orphan*/  retry; TYPE_1__ context_un; } ;
struct TYPE_14__ {int /*<<< orphan*/  elsXmitACC; } ;
struct lpfc_hba {TYPE_6__ fc_stat; struct lpfc_sli sli; } ;
struct lpfc_dmabuf {int /*<<< orphan*/ * virt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_12__ {int /*<<< orphan*/  acceptRspCode; } ;
struct TYPE_13__ {TYPE_4__ prlo; } ;
struct TYPE_16__ {TYPE_5__ un; } ;
typedef  int /*<<< orphan*/  PRLO ;
typedef  int /*<<< orphan*/  LPFC_MBOXQ_t ;
typedef  TYPE_7__ IOCB_t ;
typedef  TYPE_8__ ELS_PKT ;

/* Variables and functions */
#define  ELS_CMD_ACC 130 
#define  ELS_CMD_PLOGI 129 
#define  ELS_CMD_PRLO 128 
 int ELS_CMD_PRLO_ACC ; 
 int IOCB_ERROR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_RSP ; 
 int /*<<< orphan*/  LPFC_ELS_RING ; 
 int NLP_LOGO_ACC ; 
 int /*<<< orphan*/  PRLO_REQ_EXECUTED ; 
 int /*<<< orphan*/  lpfc_cmpl_els_logo_acc ; 
 int /*<<< orphan*/  lpfc_cmpl_els_rsp ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 struct lpfc_iocbq* lpfc_prep_els_iocb (struct lpfc_vport*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct lpfc_nodelist*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

int
lpfc_els_rsp_acc(struct lpfc_vport *vport, uint32_t flag,
		 struct lpfc_iocbq *oldiocb, struct lpfc_nodelist *ndlp,
		 LPFC_MBOXQ_t *mbox)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba  *phba = vport->phba;
	IOCB_t *icmd;
	IOCB_t *oldcmd;
	struct lpfc_iocbq *elsiocb;
	struct lpfc_sli *psli;
	uint8_t *pcmd;
	uint16_t cmdsize;
	int rc;
	ELS_PKT *els_pkt_ptr;

	psli = &phba->sli;
	oldcmd = &oldiocb->iocb;

	switch (flag) {
	case ELS_CMD_ACC:
		cmdsize = sizeof(uint32_t);
		elsiocb = lpfc_prep_els_iocb(vport, 0, cmdsize, oldiocb->retry,
					     ndlp, ndlp->nlp_DID, ELS_CMD_ACC);
		if (!elsiocb) {
			spin_lock_irq(shost->host_lock);
			ndlp->nlp_flag &= ~NLP_LOGO_ACC;
			spin_unlock_irq(shost->host_lock);
			return 1;
		}

		icmd = &elsiocb->iocb;
		icmd->ulpContext = oldcmd->ulpContext;	/* Xri / rx_id */
		icmd->unsli3.rcvsli3.ox_id = oldcmd->unsli3.rcvsli3.ox_id;
		pcmd = (((struct lpfc_dmabuf *) elsiocb->context2)->virt);
		*((uint32_t *) (pcmd)) = ELS_CMD_ACC;
		pcmd += sizeof(uint32_t);

		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_RSP,
			"Issue ACC:       did:x%x flg:x%x",
			ndlp->nlp_DID, ndlp->nlp_flag, 0);
		break;
	case ELS_CMD_PLOGI:
		cmdsize = (sizeof(struct serv_parm) + sizeof(uint32_t));
		elsiocb = lpfc_prep_els_iocb(vport, 0, cmdsize, oldiocb->retry,
					     ndlp, ndlp->nlp_DID, ELS_CMD_ACC);
		if (!elsiocb)
			return 1;

		icmd = &elsiocb->iocb;
		icmd->ulpContext = oldcmd->ulpContext;	/* Xri / rx_id */
		icmd->unsli3.rcvsli3.ox_id = oldcmd->unsli3.rcvsli3.ox_id;
		pcmd = (((struct lpfc_dmabuf *) elsiocb->context2)->virt);

		if (mbox)
			elsiocb->context_un.mbox = mbox;

		*((uint32_t *) (pcmd)) = ELS_CMD_ACC;
		pcmd += sizeof(uint32_t);
		memcpy(pcmd, &vport->fc_sparam, sizeof(struct serv_parm));

		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_RSP,
			"Issue ACC PLOGI: did:x%x flg:x%x",
			ndlp->nlp_DID, ndlp->nlp_flag, 0);
		break;
	case ELS_CMD_PRLO:
		cmdsize = sizeof(uint32_t) + sizeof(PRLO);
		elsiocb = lpfc_prep_els_iocb(vport, 0, cmdsize, oldiocb->retry,
					     ndlp, ndlp->nlp_DID, ELS_CMD_PRLO);
		if (!elsiocb)
			return 1;

		icmd = &elsiocb->iocb;
		icmd->ulpContext = oldcmd->ulpContext;	/* Xri / rx_id */
		icmd->unsli3.rcvsli3.ox_id = oldcmd->unsli3.rcvsli3.ox_id;
		pcmd = (((struct lpfc_dmabuf *) elsiocb->context2)->virt);

		memcpy(pcmd, ((struct lpfc_dmabuf *) oldiocb->context2)->virt,
		       sizeof(uint32_t) + sizeof(PRLO));
		*((uint32_t *) (pcmd)) = ELS_CMD_PRLO_ACC;
		els_pkt_ptr = (ELS_PKT *) pcmd;
		els_pkt_ptr->un.prlo.acceptRspCode = PRLO_REQ_EXECUTED;

		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_RSP,
			"Issue ACC PRLO:  did:x%x flg:x%x",
			ndlp->nlp_DID, ndlp->nlp_flag, 0);
		break;
	default:
		return 1;
	}
	/* Xmit ELS ACC response tag <ulpIoTag> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "0128 Xmit ELS ACC response tag x%x, XRI: x%x, "
			 "DID: x%x, nlp_flag: x%x nlp_state: x%x RPI: x%x "
			 "fc_flag x%x\n",
			 elsiocb->iotag, elsiocb->iocb.ulpContext,
			 ndlp->nlp_DID, ndlp->nlp_flag, ndlp->nlp_state,
			 ndlp->nlp_rpi, vport->fc_flag);
	if (ndlp->nlp_flag & NLP_LOGO_ACC) {
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag &= ~NLP_LOGO_ACC;
		spin_unlock_irq(shost->host_lock);
		elsiocb->iocb_cmpl = lpfc_cmpl_els_logo_acc;
	} else {
		elsiocb->iocb_cmpl = lpfc_cmpl_els_rsp;
	}

	phba->fc_stat.elsXmitACC++;
	rc = lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, elsiocb, 0);
	if (rc == IOCB_ERROR) {
		lpfc_els_free_iocb(phba, elsiocb);
		return 1;
	}
	return 0;
}