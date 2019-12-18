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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_11__ {scalar_t__ vendorUnique; int /*<<< orphan*/  lsRjtRsnCodeExp; int /*<<< orphan*/  lsRjtRsnCode; scalar_t__ lsRjtRsvd0; } ;
struct TYPE_12__ {int /*<<< orphan*/  lsRjtError; TYPE_5__ b; } ;
struct ls_rjt {TYPE_6__ un; } ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_rpi; int /*<<< orphan*/  nlp_state; int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  vport; } ;
struct TYPE_7__ {int /*<<< orphan*/  ox_id; } ;
struct TYPE_8__ {TYPE_1__ rcvsli3; } ;
struct TYPE_9__ {int /*<<< orphan*/  ulpContext; TYPE_2__ unsli3; } ;
struct lpfc_iocbq {int /*<<< orphan*/  iocb_cmpl; TYPE_3__ iocb; int /*<<< orphan*/  iotag; scalar_t__ context2; } ;
struct TYPE_10__ {int /*<<< orphan*/  elsXmitACC; } ;
struct lpfc_hba {int fc_ratov; int fc_edtov; TYPE_4__ fc_stat; scalar_t__ fc_edtovResol; int /*<<< orphan*/  pport; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct RTV_RSP {int qtov; void* edtov; void* ratov; } ;

/* Variables and functions */
 int ELS_CMD_ACC ; 
 scalar_t__ IOCB_ERROR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_ELS_RING ; 
 int /*<<< orphan*/  LSEXP_CANT_GIVE_DATA ; 
 int /*<<< orphan*/  LSRJT_UNABLE_TPC ; 
 int /*<<< orphan*/  NLP_STE_MAPPED_NODE ; 
 int /*<<< orphan*/  NLP_STE_UNMAPPED_NODE ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct RTV_RSP*,int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  lpfc_cmpl_els_rsp ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_els_rsp_reject (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_max_els_tries ; 
 struct lpfc_iocbq* lpfc_prep_els_iocb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct lpfc_nodelist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,int) ; 
 scalar_t__ lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtov_edtovres ; 
 int /*<<< orphan*/  qtov_rttov ; 

__attribute__((used)) static int
lpfc_els_rcv_rtv(struct lpfc_vport *vport, struct lpfc_iocbq *cmdiocb,
		 struct lpfc_nodelist *ndlp)
{
	struct lpfc_hba *phba = vport->phba;
	struct ls_rjt stat;
	struct RTV_RSP *rtv_rsp;
	uint8_t *pcmd;
	struct lpfc_iocbq *elsiocb;
	uint32_t cmdsize;


	if ((ndlp->nlp_state != NLP_STE_UNMAPPED_NODE) &&
	    (ndlp->nlp_state != NLP_STE_MAPPED_NODE))
		/* reject the unsolicited RPS request and done with it */
		goto reject_out;

	cmdsize = sizeof(struct RTV_RSP) + sizeof(uint32_t);
	elsiocb = lpfc_prep_els_iocb(phba->pport, 0, cmdsize,
				     lpfc_max_els_tries, ndlp,
				     ndlp->nlp_DID, ELS_CMD_ACC);

	if (!elsiocb)
		return 1;

	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) elsiocb->context2)->virt);
		*((uint32_t *) (pcmd)) = ELS_CMD_ACC;
	pcmd += sizeof(uint32_t); /* Skip past command */

	/* use the command's xri in the response */
	elsiocb->iocb.ulpContext = cmdiocb->iocb.ulpContext;  /* Xri / rx_id */
	elsiocb->iocb.unsli3.rcvsli3.ox_id = cmdiocb->iocb.unsli3.rcvsli3.ox_id;

	rtv_rsp = (struct RTV_RSP *)pcmd;

	/* populate RTV payload */
	rtv_rsp->ratov = cpu_to_be32(phba->fc_ratov * 1000); /* report msecs */
	rtv_rsp->edtov = cpu_to_be32(phba->fc_edtov);
	bf_set(qtov_edtovres, rtv_rsp, phba->fc_edtovResol ? 1 : 0);
	bf_set(qtov_rttov, rtv_rsp, 0); /* Field is for FC ONLY */
	rtv_rsp->qtov = cpu_to_be32(rtv_rsp->qtov);

	/* Xmit ELS RLS ACC response tag <ulpIoTag> */
	lpfc_printf_vlog(ndlp->vport, KERN_INFO, LOG_ELS,
			 "2875 Xmit ELS RTV ACC response tag x%x xri x%x, "
			 "did x%x, nlp_flag x%x, nlp_state x%x, rpi x%x, "
			 "Data: x%x x%x x%x\n",
			 elsiocb->iotag, elsiocb->iocb.ulpContext,
			 ndlp->nlp_DID, ndlp->nlp_flag, ndlp->nlp_state,
			 ndlp->nlp_rpi,
			rtv_rsp->ratov, rtv_rsp->edtov, rtv_rsp->qtov);
	elsiocb->iocb_cmpl = lpfc_cmpl_els_rsp;
	phba->fc_stat.elsXmitACC++;
	if (lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, elsiocb, 0) == IOCB_ERROR)
		lpfc_els_free_iocb(phba, elsiocb);
	return 0;

reject_out:
	/* issue rejection response */
	stat.un.b.lsRjtRsvd0 = 0;
	stat.un.b.lsRjtRsnCode = LSRJT_UNABLE_TPC;
	stat.un.b.lsRjtRsnCodeExp = LSEXP_CANT_GIVE_DATA;
	stat.un.b.vendorUnique = 0;
	lpfc_els_rsp_reject(vport, stat.un.lsRjtError, cmdiocb, ndlp, NULL);
	return 0;
}