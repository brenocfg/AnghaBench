#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct lpfc_vport {int /*<<< orphan*/  fc_portname; int /*<<< orphan*/  fc_nodename; struct lpfc_hba* phba; } ;
struct lpfc_sli {int dummy; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_DID; } ;
struct lpfc_name {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  ox_id; } ;
struct TYPE_9__ {TYPE_1__ rcvsli3; } ;
struct TYPE_14__ {int /*<<< orphan*/  ulpContext; TYPE_2__ unsli3; } ;
struct lpfc_iocbq {int /*<<< orphan*/  iocb_cmpl; scalar_t__ context2; TYPE_7__ iocb; int /*<<< orphan*/  iotag; int /*<<< orphan*/  retry; } ;
struct TYPE_12__ {int /*<<< orphan*/  elsXmitACC; } ;
struct lpfc_hba {TYPE_5__ fc_stat; struct lpfc_sli sli; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct TYPE_10__ {int /*<<< orphan*/  attachedNodes; int /*<<< orphan*/  physPort; int /*<<< orphan*/  unitType; int /*<<< orphan*/  portName; } ;
struct TYPE_11__ {TYPE_3__ topologyDisc; } ;
struct TYPE_13__ {int Format; int CommonLen; int SpecificLen; TYPE_4__ un; int /*<<< orphan*/  nodeName; int /*<<< orphan*/  portName; } ;
typedef  int /*<<< orphan*/  RNID_TOP_DISC ;
typedef  TYPE_6__ RNID ;
typedef  TYPE_7__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_CMD_ACC ; 
 int IOCB_ERROR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_RSP ; 
 int /*<<< orphan*/  LPFC_ELS_RING ; 
 int /*<<< orphan*/  RNID_HBA ; 
#define  RNID_TOPOLOGY_DISC 128 
 int /*<<< orphan*/  lpfc_cmpl_els_rsp ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 struct lpfc_iocbq* lpfc_prep_els_iocb (struct lpfc_vport*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct lpfc_nodelist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lpfc_els_rsp_rnid_acc(struct lpfc_vport *vport, uint8_t format,
		      struct lpfc_iocbq *oldiocb, struct lpfc_nodelist *ndlp)
{
	struct lpfc_hba  *phba = vport->phba;
	RNID *rn;
	IOCB_t *icmd, *oldcmd;
	struct lpfc_iocbq *elsiocb;
	struct lpfc_sli *psli;
	uint8_t *pcmd;
	uint16_t cmdsize;
	int rc;

	psli = &phba->sli;
	cmdsize = sizeof(uint32_t) + sizeof(uint32_t)
					+ (2 * sizeof(struct lpfc_name));
	if (format)
		cmdsize += sizeof(RNID_TOP_DISC);

	elsiocb = lpfc_prep_els_iocb(vport, 0, cmdsize, oldiocb->retry, ndlp,
				     ndlp->nlp_DID, ELS_CMD_ACC);
	if (!elsiocb)
		return 1;

	icmd = &elsiocb->iocb;
	oldcmd = &oldiocb->iocb;
	icmd->ulpContext = oldcmd->ulpContext;	/* Xri / rx_id */
	icmd->unsli3.rcvsli3.ox_id = oldcmd->unsli3.rcvsli3.ox_id;

	/* Xmit RNID ACC response tag <ulpIoTag> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "0132 Xmit RNID ACC response tag x%x xri x%x\n",
			 elsiocb->iotag, elsiocb->iocb.ulpContext);
	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) elsiocb->context2)->virt);
	*((uint32_t *) (pcmd)) = ELS_CMD_ACC;
	pcmd += sizeof(uint32_t);

	memset(pcmd, 0, sizeof(RNID));
	rn = (RNID *) (pcmd);
	rn->Format = format;
	rn->CommonLen = (2 * sizeof(struct lpfc_name));
	memcpy(&rn->portName, &vport->fc_portname, sizeof(struct lpfc_name));
	memcpy(&rn->nodeName, &vport->fc_nodename, sizeof(struct lpfc_name));
	switch (format) {
	case 0:
		rn->SpecificLen = 0;
		break;
	case RNID_TOPOLOGY_DISC:
		rn->SpecificLen = sizeof(RNID_TOP_DISC);
		memcpy(&rn->un.topologyDisc.portName,
		       &vport->fc_portname, sizeof(struct lpfc_name));
		rn->un.topologyDisc.unitType = RNID_HBA;
		rn->un.topologyDisc.physPort = 0;
		rn->un.topologyDisc.attachedNodes = 0;
		break;
	default:
		rn->CommonLen = 0;
		rn->SpecificLen = 0;
		break;
	}

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_RSP,
		"Issue ACC RNID:  did:x%x flg:x%x",
		ndlp->nlp_DID, ndlp->nlp_flag, 0);

	phba->fc_stat.elsXmitACC++;
	elsiocb->iocb_cmpl = lpfc_cmpl_els_rsp;

	rc = lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, elsiocb, 0);
	if (rc == IOCB_ERROR) {
		lpfc_els_free_iocb(phba, elsiocb);
		return 1;
	}
	return 0;
}