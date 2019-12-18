#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_17__ {scalar_t__ r_a_tov; } ;
struct TYPE_23__ {scalar_t__ fcphLow; scalar_t__ fcphHigh; int request_multiple_Nport; scalar_t__ virtual_fabric_support; TYPE_2__ w2; scalar_t__ e_d_tov; } ;
struct TYPE_22__ {int seqDelivery; scalar_t__ classValid; } ;
struct TYPE_21__ {int seqDelivery; scalar_t__ classValid; } ;
struct TYPE_18__ {scalar_t__ classValid; } ;
struct serv_parm {TYPE_8__ cmn; TYPE_7__ cls3; TYPE_6__ cls2; TYPE_3__ cls1; } ;
struct lpfc_vport {int /*<<< orphan*/  fc_sparam; struct lpfc_hba* phba; } ;
struct lpfc_sli_ring {int dummy; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; } ;
struct TYPE_24__ {int fl; scalar_t__ myID; } ;
struct TYPE_13__ {TYPE_9__ elsreq64; } ;
struct TYPE_15__ {int ulpCt_h; int ulpCt_l; TYPE_10__ un; int /*<<< orphan*/  ulpContext; } ;
struct lpfc_iocbq {int /*<<< orphan*/  iocb_cmpl; TYPE_12__ iocb; scalar_t__ context2; } ;
struct TYPE_14__ {int /*<<< orphan*/  elsXmitFLOGI; } ;
struct TYPE_20__ {int /*<<< orphan*/  fcfi; } ;
struct TYPE_19__ {int /*<<< orphan*/  sli_intf; } ;
struct TYPE_16__ {struct lpfc_sli_ring* ring; } ;
struct lpfc_hba {scalar_t__ sli_rev; int sli3_options; scalar_t__ fc_topology; TYPE_11__ fc_stat; int /*<<< orphan*/  fc_ratov; TYPE_5__ fcf; TYPE_4__ sli4_hba; TYPE_1__ sli; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
typedef  TYPE_12__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_FLOGI ; 
 scalar_t__ FC_PH3 ; 
 int IOCB_ERROR ; 
 int /*<<< orphan*/  LPFC_DISC_FLOGI_TMO ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_CMD ; 
 size_t LPFC_ELS_RING ; 
 int LPFC_SLI3_NPIV_ENABLED ; 
 scalar_t__ LPFC_SLI_INTF_IF_TYPE_0 ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 
 int SLI4_CT_FCFI ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_cmpl_els_flogi ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int lpfc_issue_fabric_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 struct lpfc_iocbq* lpfc_prep_els_iocb (struct lpfc_vport*,int,int,int /*<<< orphan*/ ,struct lpfc_nodelist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_set_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lpfc_issue_els_flogi(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
		     uint8_t retry)
{
	struct lpfc_hba  *phba = vport->phba;
	struct serv_parm *sp;
	IOCB_t *icmd;
	struct lpfc_iocbq *elsiocb;
	struct lpfc_sli_ring *pring;
	uint8_t *pcmd;
	uint16_t cmdsize;
	uint32_t tmo;
	int rc;

	pring = &phba->sli.ring[LPFC_ELS_RING];

	cmdsize = (sizeof(uint32_t) + sizeof(struct serv_parm));
	elsiocb = lpfc_prep_els_iocb(vport, 1, cmdsize, retry, ndlp,
				     ndlp->nlp_DID, ELS_CMD_FLOGI);

	if (!elsiocb)
		return 1;

	icmd = &elsiocb->iocb;
	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) elsiocb->context2)->virt);

	/* For FLOGI request, remainder of payload is service parameters */
	*((uint32_t *) (pcmd)) = ELS_CMD_FLOGI;
	pcmd += sizeof(uint32_t);
	memcpy(pcmd, &vport->fc_sparam, sizeof(struct serv_parm));
	sp = (struct serv_parm *) pcmd;

	/* Setup CSPs accordingly for Fabric */
	sp->cmn.e_d_tov = 0;
	sp->cmn.w2.r_a_tov = 0;
	sp->cmn.virtual_fabric_support = 0;
	sp->cls1.classValid = 0;
	if (sp->cmn.fcphLow < FC_PH3)
		sp->cmn.fcphLow = FC_PH3;
	if (sp->cmn.fcphHigh < FC_PH3)
		sp->cmn.fcphHigh = FC_PH3;

	if  (phba->sli_rev == LPFC_SLI_REV4) {
		if (bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf) ==
		    LPFC_SLI_INTF_IF_TYPE_0) {
			elsiocb->iocb.ulpCt_h = ((SLI4_CT_FCFI >> 1) & 1);
			elsiocb->iocb.ulpCt_l = (SLI4_CT_FCFI & 1);
			/* FLOGI needs to be 3 for WQE FCFI */
			/* Set the fcfi to the fcfi we registered with */
			elsiocb->iocb.ulpContext = phba->fcf.fcfi;
		}
		/* Can't do SLI4 class2 without support sequence coalescing */
		sp->cls2.classValid = 0;
		sp->cls2.seqDelivery = 0;
	} else {
		/* Historical, setting sequential-delivery bit for SLI3 */
		sp->cls2.seqDelivery = (sp->cls2.classValid) ? 1 : 0;
		sp->cls3.seqDelivery = (sp->cls3.classValid) ? 1 : 0;
		if (phba->sli3_options & LPFC_SLI3_NPIV_ENABLED) {
			sp->cmn.request_multiple_Nport = 1;
			/* For FLOGI, Let FLOGI rsp set the NPortID for VPI 0 */
			icmd->ulpCt_h = 1;
			icmd->ulpCt_l = 0;
		} else
			sp->cmn.request_multiple_Nport = 0;
	}

	if (phba->fc_topology != LPFC_TOPOLOGY_LOOP) {
		icmd->un.elsreq64.myID = 0;
		icmd->un.elsreq64.fl = 1;
	}

	tmo = phba->fc_ratov;
	phba->fc_ratov = LPFC_DISC_FLOGI_TMO;
	lpfc_set_disctmo(vport);
	phba->fc_ratov = tmo;

	phba->fc_stat.elsXmitFLOGI++;
	elsiocb->iocb_cmpl = lpfc_cmpl_els_flogi;

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"Issue FLOGI:     opt:x%x",
		phba->sli3_options, 0, 0);

	rc = lpfc_issue_fabric_iocb(phba, elsiocb);
	if (rc == IOCB_ERROR) {
		lpfc_els_free_iocb(phba, elsiocb);
		return 1;
	}
	return 0;
}