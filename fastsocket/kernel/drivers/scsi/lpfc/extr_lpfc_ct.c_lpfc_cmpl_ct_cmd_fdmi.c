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
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct lpfc_vport {int dummy; } ;
struct TYPE_5__ {int CmdRsp; } ;
struct TYPE_6__ {TYPE_1__ bits; } ;
struct lpfc_sli_ct_request {TYPE_2__ CommandResponse; } ;
struct lpfc_nodelist {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ulpWord; } ;
struct TYPE_8__ {TYPE_3__ un; scalar_t__ ulpStatus; } ;
struct lpfc_iocbq {TYPE_4__ iocb; struct lpfc_vport* vport; struct lpfc_dmabuf* context2; struct lpfc_dmabuf* context1; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {struct lpfc_sli_ct_request* virt; } ;
typedef  TYPE_4__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  FDMI_DID ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_CT ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int SLI_CT_RESPONSE_FS_RJT ; 
#define  SLI_MGMT_DHBA 131 
#define  SLI_MGMT_DPRT 130 
#define  SLI_MGMT_RHBA 129 
#define  SLI_MGMT_RPA 128 
 int be16_to_cpu (int) ; 
 int /*<<< orphan*/  lpfc_ct_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lpfc_els_chk_latt (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_fdmi_cmd (struct lpfc_vport*,struct lpfc_nodelist*,int const) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void
lpfc_cmpl_ct_cmd_fdmi(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
		      struct lpfc_iocbq * rspiocb)
{
	struct lpfc_dmabuf *inp = cmdiocb->context1;
	struct lpfc_dmabuf *outp = cmdiocb->context2;
	struct lpfc_sli_ct_request *CTrsp = outp->virt;
	struct lpfc_sli_ct_request *CTcmd = inp->virt;
	struct lpfc_nodelist *ndlp;
	uint16_t fdmi_cmd = CTcmd->CommandResponse.bits.CmdRsp;
	uint16_t fdmi_rsp = CTrsp->CommandResponse.bits.CmdRsp;
	struct lpfc_vport *vport = cmdiocb->vport;
	IOCB_t *irsp = &rspiocb->iocb;
	uint32_t latt;

	latt = lpfc_els_chk_latt(vport);

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
		"FDMI cmpl:       status:x%x/x%x latt:%d",
		irsp->ulpStatus, irsp->un.ulpWord[4], latt);

	if (latt || irsp->ulpStatus) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
				 "0229 FDMI cmd %04x failed, latt = %d "
				 "ulpStatus: x%x, rid x%x\n",
				 be16_to_cpu(fdmi_cmd), latt, irsp->ulpStatus,
				 irsp->un.ulpWord[4]);
		lpfc_ct_free_iocb(phba, cmdiocb);
		return;
	}

	ndlp = lpfc_findnode_did(vport, FDMI_DID);
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp))
		goto fail_out;

	if (fdmi_rsp == be16_to_cpu(SLI_CT_RESPONSE_FS_RJT)) {
		/* FDMI rsp failed */
		lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
				 "0220 FDMI rsp failed Data: x%x\n",
				 be16_to_cpu(fdmi_cmd));
	}

	switch (be16_to_cpu(fdmi_cmd)) {
	case SLI_MGMT_RHBA:
		lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_RPA);
		break;

	case SLI_MGMT_RPA:
		break;

	case SLI_MGMT_DHBA:
		lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_DPRT);
		break;

	case SLI_MGMT_DPRT:
		lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_RHBA);
		break;
	}

fail_out:
	lpfc_ct_free_iocb(phba, cmdiocb);
	return;
}