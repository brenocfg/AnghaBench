#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_sli_ring {int /*<<< orphan*/  ringno; } ;
struct TYPE_6__ {int /*<<< orphan*/  abortIoTag; int /*<<< orphan*/  abortContextTag; int /*<<< orphan*/  abortType; } ;
struct TYPE_7__ {TYPE_2__ acxri; } ;
struct TYPE_8__ {int ulpLe; int /*<<< orphan*/  ulpCommand; int /*<<< orphan*/  ulpClass; int /*<<< orphan*/  ulpIoTag; TYPE_3__ un; int /*<<< orphan*/  ulpContext; } ;
struct lpfc_iocbq {int iocb_flag; int /*<<< orphan*/  iocb_cmpl; TYPE_4__ iocb; int /*<<< orphan*/  fcp_wqidx; int /*<<< orphan*/  vport; int /*<<< orphan*/  sli4_xritag; } ;
struct TYPE_5__ {int last_iotag; struct lpfc_iocbq** iocbq_lookup; } ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  pport; TYPE_1__ sli; } ;
typedef  int /*<<< orphan*/  lpfc_ctx_cmd ;
typedef  TYPE_4__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_TYPE_ABTS ; 
 int /*<<< orphan*/  CMD_ABORT_XRI_CN ; 
 int /*<<< orphan*/  CMD_CLOSE_XRI_CN ; 
 int IOCB_ERROR ; 
 int LPFC_IO_FCP ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int LPFC_USE_FCPWQIDX ; 
 scalar_t__ lpfc_is_link_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_abort_fcp_cmpl ; 
 struct lpfc_iocbq* lpfc_sli_get_iocbq (struct lpfc_hba*) ; 
 int lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 scalar_t__ lpfc_sli_validate_fcp_iocb (struct lpfc_iocbq*,struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
lpfc_sli_abort_iocb(struct lpfc_vport *vport, struct lpfc_sli_ring *pring,
		    uint16_t tgt_id, uint64_t lun_id, lpfc_ctx_cmd abort_cmd)
{
	struct lpfc_hba *phba = vport->phba;
	struct lpfc_iocbq *iocbq;
	struct lpfc_iocbq *abtsiocb;
	IOCB_t *cmd = NULL;
	int errcnt = 0, ret_val = 0;
	int i;

	for (i = 1; i <= phba->sli.last_iotag; i++) {
		iocbq = phba->sli.iocbq_lookup[i];

		if (lpfc_sli_validate_fcp_iocb(iocbq, vport, tgt_id, lun_id,
					       abort_cmd) != 0)
			continue;

		/* issue ABTS for this IOCB based on iotag */
		abtsiocb = lpfc_sli_get_iocbq(phba);
		if (abtsiocb == NULL) {
			errcnt++;
			continue;
		}

		cmd = &iocbq->iocb;
		abtsiocb->iocb.un.acxri.abortType = ABORT_TYPE_ABTS;
		abtsiocb->iocb.un.acxri.abortContextTag = cmd->ulpContext;
		if (phba->sli_rev == LPFC_SLI_REV4)
			abtsiocb->iocb.un.acxri.abortIoTag = iocbq->sli4_xritag;
		else
			abtsiocb->iocb.un.acxri.abortIoTag = cmd->ulpIoTag;
		abtsiocb->iocb.ulpLe = 1;
		abtsiocb->iocb.ulpClass = cmd->ulpClass;
		abtsiocb->vport = phba->pport;

		/* ABTS WQE must go to the same WQ as the WQE to be aborted */
		abtsiocb->fcp_wqidx = iocbq->fcp_wqidx;
		if (iocbq->iocb_flag & LPFC_IO_FCP)
			abtsiocb->iocb_flag |= LPFC_USE_FCPWQIDX;

		if (lpfc_is_link_up(phba))
			abtsiocb->iocb.ulpCommand = CMD_ABORT_XRI_CN;
		else
			abtsiocb->iocb.ulpCommand = CMD_CLOSE_XRI_CN;

		/* Setup callback routine and issue the command. */
		abtsiocb->iocb_cmpl = lpfc_sli_abort_fcp_cmpl;
		ret_val = lpfc_sli_issue_iocb(phba, pring->ringno,
					      abtsiocb, 0);
		if (ret_val == IOCB_ERROR) {
			lpfc_sli_release_iocbq(phba, abtsiocb);
			errcnt++;
			continue;
		}
	}

	return errcnt;
}