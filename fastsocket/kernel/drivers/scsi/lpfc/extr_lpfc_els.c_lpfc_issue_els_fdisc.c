#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_19__ {int seqDelivery; } ;
struct TYPE_18__ {int seqDelivery; } ;
struct TYPE_17__ {scalar_t__ classValid; } ;
struct TYPE_15__ {scalar_t__ r_a_tov; } ;
struct TYPE_16__ {scalar_t__ virtual_fabric_support; TYPE_4__ w2; scalar_t__ e_d_tov; } ;
struct serv_parm {TYPE_8__ cls3; TYPE_7__ cls2; TYPE_6__ cls1; TYPE_5__ cmn; } ;
struct lpfc_vport {int /*<<< orphan*/  fc_nodename; int /*<<< orphan*/  fc_portname; struct lpfc_hba* phba; scalar_t__ fc_myDID; int /*<<< orphan*/  port_state; } ;
struct lpfc_nodelist {int nlp_DID; } ;
struct TYPE_12__ {int fl; scalar_t__ myID; } ;
struct TYPE_13__ {TYPE_1__ elsreq64; } ;
struct TYPE_11__ {int ulpCt_h; scalar_t__ ulpCt_l; TYPE_2__ un; } ;
struct lpfc_iocbq {int /*<<< orphan*/  iocb_cmpl; scalar_t__ context2; TYPE_10__ iocb; } ;
struct TYPE_20__ {int /*<<< orphan*/  elsXmitFDISC; } ;
struct lpfc_hba {scalar_t__ sli_rev; TYPE_9__ fc_stat; TYPE_3__* pport; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct TYPE_14__ {int /*<<< orphan*/  fc_sparam; } ;
typedef  TYPE_10__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_FDISC ; 
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int /*<<< orphan*/  FC_VPORT_INITIALIZING ; 
 int IOCB_ERROR ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_CMD ; 
 int /*<<< orphan*/  LPFC_FDISC ; 
 scalar_t__ LPFC_SLI_REV3 ; 
 int /*<<< orphan*/  lpfc_cmpl_els_fdisc ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int lpfc_issue_fabric_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 struct lpfc_iocbq* lpfc_prep_els_iocb (struct lpfc_vport*,int,int,int /*<<< orphan*/ ,struct lpfc_nodelist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_set_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lpfc_issue_els_fdisc(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
		     uint8_t retry)
{
	struct lpfc_hba *phba = vport->phba;
	IOCB_t *icmd;
	struct lpfc_iocbq *elsiocb;
	struct serv_parm *sp;
	uint8_t *pcmd;
	uint16_t cmdsize;
	int did = ndlp->nlp_DID;
	int rc;

	vport->port_state = LPFC_FDISC;
	vport->fc_myDID = 0;
	cmdsize = (sizeof(uint32_t) + sizeof(struct serv_parm));
	elsiocb = lpfc_prep_els_iocb(vport, 1, cmdsize, retry, ndlp, did,
				     ELS_CMD_FDISC);
	if (!elsiocb) {
		lpfc_vport_set_state(vport, FC_VPORT_FAILED);
		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
				 "0255 Issue FDISC: no IOCB\n");
		return 1;
	}

	icmd = &elsiocb->iocb;
	icmd->un.elsreq64.myID = 0;
	icmd->un.elsreq64.fl = 1;

	/*
	 * SLI3 ports require a different context type value than SLI4.
	 * Catch SLI3 ports here and override the prep.
	 */
	if (phba->sli_rev == LPFC_SLI_REV3) {
		icmd->ulpCt_h = 1;
		icmd->ulpCt_l = 0;
	}

	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) elsiocb->context2)->virt);
	*((uint32_t *) (pcmd)) = ELS_CMD_FDISC;
	pcmd += sizeof(uint32_t); /* CSP Word 1 */
	memcpy(pcmd, &vport->phba->pport->fc_sparam, sizeof(struct serv_parm));
	sp = (struct serv_parm *) pcmd;
	/* Setup CSPs accordingly for Fabric */
	sp->cmn.e_d_tov = 0;
	sp->cmn.w2.r_a_tov = 0;
	sp->cmn.virtual_fabric_support = 0;
	sp->cls1.classValid = 0;
	sp->cls2.seqDelivery = 1;
	sp->cls3.seqDelivery = 1;

	pcmd += sizeof(uint32_t); /* CSP Word 2 */
	pcmd += sizeof(uint32_t); /* CSP Word 3 */
	pcmd += sizeof(uint32_t); /* CSP Word 4 */
	pcmd += sizeof(uint32_t); /* Port Name */
	memcpy(pcmd, &vport->fc_portname, 8);
	pcmd += sizeof(uint32_t); /* Node Name */
	pcmd += sizeof(uint32_t); /* Node Name */
	memcpy(pcmd, &vport->fc_nodename, 8);

	lpfc_set_disctmo(vport);

	phba->fc_stat.elsXmitFDISC++;
	elsiocb->iocb_cmpl = lpfc_cmpl_els_fdisc;

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"Issue FDISC:     did:x%x",
		did, 0, 0);

	rc = lpfc_issue_fabric_iocb(phba, elsiocb);
	if (rc == IOCB_ERROR) {
		lpfc_els_free_iocb(phba, elsiocb);
		lpfc_vport_set_state(vport, FC_VPORT_FAILED);
		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
				 "0256 Issue FDISC: Cannot send IOCB\n");
		return 1;
	}
	lpfc_vport_set_state(vport, FC_VPORT_INITIALIZING);
	return 0;
}