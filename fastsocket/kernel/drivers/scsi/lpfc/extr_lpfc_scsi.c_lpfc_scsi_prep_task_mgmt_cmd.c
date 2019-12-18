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
struct lpfc_vport {TYPE_5__* phba; } ;
struct TYPE_6__ {int /*<<< orphan*/  icd; } ;
struct TYPE_7__ {TYPE_1__ fcp_ext; } ;
struct TYPE_9__ {size_t ulpContext; int ulpFCP2Rcvy; int ulpClass; int ulpTimeout; int /*<<< orphan*/  ulpCommand; TYPE_2__ unsli3; } ;
struct lpfc_iocbq {TYPE_4__ iocb; struct lpfc_vport* vport; } ;
struct lpfc_scsi_buf {int timeout; struct fcp_cmnd* fcp_cmnd; struct lpfc_iocbq cur_iocbq; struct lpfc_rport_data* rdata; } ;
struct lpfc_rport_data {struct lpfc_nodelist* pnode; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; size_t nlp_rpi; int nlp_fcp_info; } ;
struct fcp_cmnd {int /*<<< orphan*/  fcpCntl2; int /*<<< orphan*/  fcp_lun; } ;
struct TYPE_8__ {size_t* rpi_ids; } ;
struct TYPE_10__ {int sli_rev; int sli3_options; TYPE_3__ sli4_hba; } ;
typedef  TYPE_4__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FCP_ICMND64_CR ; 
 int LPFC_SLI3_BG_ENABLED ; 
 int LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int NLP_FCP_2_DEVICE ; 
 scalar_t__ NLP_STE_MAPPED_NODE ; 
 int /*<<< orphan*/  int_to_scsilun (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_fcpcmd_to_iocb (int /*<<< orphan*/ ,struct fcp_cmnd*) ; 
 int /*<<< orphan*/  lpfc_sli4_set_rsp_sgl_last (TYPE_5__*,struct lpfc_scsi_buf*) ; 
 int /*<<< orphan*/  memset (struct fcp_cmnd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lpfc_scsi_prep_task_mgmt_cmd(struct lpfc_vport *vport,
			     struct lpfc_scsi_buf *lpfc_cmd,
			     unsigned int lun,
			     uint8_t task_mgmt_cmd)
{
	struct lpfc_iocbq *piocbq;
	IOCB_t *piocb;
	struct fcp_cmnd *fcp_cmnd;
	struct lpfc_rport_data *rdata = lpfc_cmd->rdata;
	struct lpfc_nodelist *ndlp = rdata->pnode;

	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp) ||
	    ndlp->nlp_state != NLP_STE_MAPPED_NODE)
		return 0;

	piocbq = &(lpfc_cmd->cur_iocbq);
	piocbq->vport = vport;

	piocb = &piocbq->iocb;

	fcp_cmnd = lpfc_cmd->fcp_cmnd;
	/* Clear out any old data in the FCP command area */
	memset(fcp_cmnd, 0, sizeof(struct fcp_cmnd));
	int_to_scsilun(lun, &fcp_cmnd->fcp_lun);
	fcp_cmnd->fcpCntl2 = task_mgmt_cmd;
	if (vport->phba->sli_rev == 3 &&
	    !(vport->phba->sli3_options & LPFC_SLI3_BG_ENABLED))
		lpfc_fcpcmd_to_iocb(piocb->unsli3.fcp_ext.icd, fcp_cmnd);
	piocb->ulpCommand = CMD_FCP_ICMND64_CR;
	piocb->ulpContext = ndlp->nlp_rpi;
	if (vport->phba->sli_rev == LPFC_SLI_REV4) {
		piocb->ulpContext =
		  vport->phba->sli4_hba.rpi_ids[ndlp->nlp_rpi];
	}
	if (ndlp->nlp_fcp_info & NLP_FCP_2_DEVICE) {
		piocb->ulpFCP2Rcvy = 1;
	}
	piocb->ulpClass = (ndlp->nlp_fcp_info & 0x0f);

	/* ulpTimeout is only one byte */
	if (lpfc_cmd->timeout > 0xff) {
		/*
		 * Do not timeout the command at the firmware level.
		 * The driver will provide the timeout mechanism.
		 */
		piocb->ulpTimeout = 0;
	} else
		piocb->ulpTimeout = lpfc_cmd->timeout;

	if (vport->phba->sli_rev == LPFC_SLI_REV4)
		lpfc_sli4_set_rsp_sgl_last(vport->phba, lpfc_cmd);

	return 1;
}