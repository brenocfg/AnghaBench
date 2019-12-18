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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_sli {int dummy; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  nlp_rpi; int /*<<< orphan*/  nlp_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  ox_id; } ;
struct TYPE_7__ {TYPE_1__ rcvsli3; } ;
struct TYPE_10__ {int /*<<< orphan*/  ulpContext; TYPE_2__ unsli3; } ;
struct TYPE_8__ {int /*<<< orphan*/ * mbox; } ;
struct lpfc_iocbq {int /*<<< orphan*/  iocb_cmpl; TYPE_5__ iocb; int /*<<< orphan*/  iotag; TYPE_3__ context_un; scalar_t__ context2; int /*<<< orphan*/  retry; } ;
struct TYPE_9__ {int /*<<< orphan*/  elsXmitLSRJT; } ;
struct lpfc_hba {TYPE_4__ fc_stat; struct lpfc_sli sli; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
typedef  int /*<<< orphan*/  LPFC_MBOXQ_t ;
typedef  TYPE_5__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_LS_RJT ; 
 int IOCB_ERROR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_RSP ; 
 int /*<<< orphan*/  LPFC_ELS_RING ; 
 int /*<<< orphan*/  lpfc_cmpl_els_rsp ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 struct lpfc_iocbq* lpfc_prep_els_iocb (struct lpfc_vport*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct lpfc_nodelist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 

int
lpfc_els_rsp_reject(struct lpfc_vport *vport, uint32_t rejectError,
		    struct lpfc_iocbq *oldiocb, struct lpfc_nodelist *ndlp,
		    LPFC_MBOXQ_t *mbox)
{
	struct lpfc_hba  *phba = vport->phba;
	IOCB_t *icmd;
	IOCB_t *oldcmd;
	struct lpfc_iocbq *elsiocb;
	struct lpfc_sli *psli;
	uint8_t *pcmd;
	uint16_t cmdsize;
	int rc;

	psli = &phba->sli;
	cmdsize = 2 * sizeof(uint32_t);
	elsiocb = lpfc_prep_els_iocb(vport, 0, cmdsize, oldiocb->retry, ndlp,
				     ndlp->nlp_DID, ELS_CMD_LS_RJT);
	if (!elsiocb)
		return 1;

	icmd = &elsiocb->iocb;
	oldcmd = &oldiocb->iocb;
	icmd->ulpContext = oldcmd->ulpContext;	/* Xri / rx_id */
	icmd->unsli3.rcvsli3.ox_id = oldcmd->unsli3.rcvsli3.ox_id;
	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) elsiocb->context2)->virt);

	*((uint32_t *) (pcmd)) = ELS_CMD_LS_RJT;
	pcmd += sizeof(uint32_t);
	*((uint32_t *) (pcmd)) = rejectError;

	if (mbox)
		elsiocb->context_un.mbox = mbox;

	/* Xmit ELS RJT <err> response tag <ulpIoTag> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "0129 Xmit ELS RJT x%x response tag x%x "
			 "xri x%x, did x%x, nlp_flag x%x, nlp_state x%x, "
			 "rpi x%x\n",
			 rejectError, elsiocb->iotag,
			 elsiocb->iocb.ulpContext, ndlp->nlp_DID,
			 ndlp->nlp_flag, ndlp->nlp_state, ndlp->nlp_rpi);
	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_RSP,
		"Issue LS_RJT:    did:x%x flg:x%x err:x%x",
		ndlp->nlp_DID, ndlp->nlp_flag, rejectError);

	phba->fc_stat.elsXmitLSRJT++;
	elsiocb->iocb_cmpl = lpfc_cmpl_els_rsp;
	rc = lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, elsiocb, 0);

	if (rc == IOCB_ERROR) {
		lpfc_els_free_iocb(phba, elsiocb);
		return 1;
	}
	return 0;
}