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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {scalar_t__ bdeFlags; int /*<<< orphan*/  bdeSize; } ;
struct TYPE_12__ {void* w; TYPE_3__ f; } ;
struct ulp_bde64 {TYPE_4__ tus; void* addrHigh; void* addrLow; } ;
struct lpfc_vport {int fc_flag; size_t vpi; int /*<<< orphan*/  port_state; int /*<<< orphan*/  fc_myDID; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; } ;
struct TYPE_13__ {int bdeSize; void* bdeFlags; void* addrLow; void* addrHigh; } ;
struct TYPE_14__ {int /*<<< orphan*/  myID; scalar_t__ remoteID; TYPE_5__ bdl; } ;
struct TYPE_9__ {int bdeSize; void* bdeFlags; void* addrLow; void* addrHigh; } ;
struct TYPE_10__ {scalar_t__ xmit_els_remoteID; TYPE_1__ bdl; } ;
struct TYPE_15__ {TYPE_6__ elsreq64; TYPE_2__ xseq64; } ;
struct TYPE_16__ {int ulpTimeout; int ulpBdeCount; int ulpLe; int ulpCt_l; scalar_t__ ulpCt_h; int /*<<< orphan*/  ulpContext; TYPE_7__ un; int /*<<< orphan*/  ulpClass; int /*<<< orphan*/  ulpCommand; } ;
struct lpfc_iocbq {int iocb_flag; int /*<<< orphan*/  iotag; scalar_t__ drvrTimeout; struct lpfc_vport* vport; scalar_t__ retry; struct lpfc_dmabuf* context3; struct lpfc_dmabuf* context2; int /*<<< orphan*/  context1; TYPE_8__ iocb; } ;
struct lpfc_hba {int hba_flag; int fc_ratov; int sli3_options; scalar_t__ sli_rev; int /*<<< orphan*/ * vpi_ids; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; void* virt; int /*<<< orphan*/  list; } ;
typedef  TYPE_8__ IOCB_t ;

/* Variables and functions */
 scalar_t__ BUFF_TYPE_BDE_64 ; 
 void* BUFF_TYPE_BLP_64 ; 
 int /*<<< orphan*/  CLASS3 ; 
 int /*<<< orphan*/  CMD_ELS_REQUEST64_CR ; 
 int /*<<< orphan*/  CMD_XMIT_ELS_RSP64_CX ; 
 scalar_t__ ELS_CMD_ECHO ; 
#define  ELS_CMD_FDISC 130 
#define  ELS_CMD_FLOGI 129 
#define  ELS_CMD_LOGO 128 
 int /*<<< orphan*/  FCELSSIZE ; 
 int FC_PT2PT ; 
 int FF_DEF_RATOV ; 
 scalar_t__ Fabric_DID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HBA_FIP_SUPPORT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 scalar_t__ LPFC_DRVR_TIMEOUT ; 
 int LPFC_ELS_ID_FDISC ; 
 int LPFC_ELS_ID_FLOGI ; 
 int LPFC_ELS_ID_LOGO ; 
 int LPFC_FIP_ELS_ID_MASK ; 
 int LPFC_FIP_ELS_ID_SHIFT ; 
 int LPFC_SLI3_NPIV_ENABLED ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  MEM_PRI ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 struct lpfc_dmabuf* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (void*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_is_link_up (struct lpfc_hba*) ; 
 void* lpfc_mbuf_alloc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_get (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 struct lpfc_iocbq* lpfc_sli_get_iocbq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 void* putPaddrHigh (int /*<<< orphan*/ ) ; 
 void* putPaddrLow (int /*<<< orphan*/ ) ; 

struct lpfc_iocbq *
lpfc_prep_els_iocb(struct lpfc_vport *vport, uint8_t expectRsp,
		   uint16_t cmdSize, uint8_t retry,
		   struct lpfc_nodelist *ndlp, uint32_t did,
		   uint32_t elscmd)
{
	struct lpfc_hba  *phba = vport->phba;
	struct lpfc_iocbq *elsiocb;
	struct lpfc_dmabuf *pcmd, *prsp, *pbuflist;
	struct ulp_bde64 *bpl;
	IOCB_t *icmd;


	if (!lpfc_is_link_up(phba))
		return NULL;

	/* Allocate buffer for  command iocb */
	elsiocb = lpfc_sli_get_iocbq(phba);

	if (elsiocb == NULL)
		return NULL;

	/*
	 * If this command is for fabric controller and HBA running
	 * in FIP mode send FLOGI, FDISC and LOGO as FIP frames.
	 */
	if ((did == Fabric_DID) &&
		(phba->hba_flag & HBA_FIP_SUPPORT) &&
		((elscmd == ELS_CMD_FLOGI) ||
		 (elscmd == ELS_CMD_FDISC) ||
		 (elscmd == ELS_CMD_LOGO)))
		switch (elscmd) {
		case ELS_CMD_FLOGI:
		elsiocb->iocb_flag |=
			((LPFC_ELS_ID_FLOGI << LPFC_FIP_ELS_ID_SHIFT)
					& LPFC_FIP_ELS_ID_MASK);
		break;
		case ELS_CMD_FDISC:
		elsiocb->iocb_flag |=
			((LPFC_ELS_ID_FDISC << LPFC_FIP_ELS_ID_SHIFT)
					& LPFC_FIP_ELS_ID_MASK);
		break;
		case ELS_CMD_LOGO:
		elsiocb->iocb_flag |=
			((LPFC_ELS_ID_LOGO << LPFC_FIP_ELS_ID_SHIFT)
					& LPFC_FIP_ELS_ID_MASK);
		break;
		}
	else
		elsiocb->iocb_flag &= ~LPFC_FIP_ELS_ID_MASK;

	icmd = &elsiocb->iocb;

	/* fill in BDEs for command */
	/* Allocate buffer for command payload */
	pcmd = kmalloc(sizeof(struct lpfc_dmabuf), GFP_KERNEL);
	if (pcmd)
		pcmd->virt = lpfc_mbuf_alloc(phba, MEM_PRI, &pcmd->phys);
	if (!pcmd || !pcmd->virt)
		goto els_iocb_free_pcmb_exit;

	INIT_LIST_HEAD(&pcmd->list);

	/* Allocate buffer for response payload */
	if (expectRsp) {
		prsp = kmalloc(sizeof(struct lpfc_dmabuf), GFP_KERNEL);
		if (prsp)
			prsp->virt = lpfc_mbuf_alloc(phba, MEM_PRI,
						     &prsp->phys);
		if (!prsp || !prsp->virt)
			goto els_iocb_free_prsp_exit;
		INIT_LIST_HEAD(&prsp->list);
	} else
		prsp = NULL;

	/* Allocate buffer for Buffer ptr list */
	pbuflist = kmalloc(sizeof(struct lpfc_dmabuf), GFP_KERNEL);
	if (pbuflist)
		pbuflist->virt = lpfc_mbuf_alloc(phba, MEM_PRI,
						 &pbuflist->phys);
	if (!pbuflist || !pbuflist->virt)
		goto els_iocb_free_pbuf_exit;

	INIT_LIST_HEAD(&pbuflist->list);

	if (expectRsp) {
		icmd->un.elsreq64.bdl.addrHigh = putPaddrHigh(pbuflist->phys);
		icmd->un.elsreq64.bdl.addrLow = putPaddrLow(pbuflist->phys);
		icmd->un.elsreq64.bdl.bdeFlags = BUFF_TYPE_BLP_64;
		icmd->un.elsreq64.bdl.bdeSize = (2 * sizeof(struct ulp_bde64));

		icmd->un.elsreq64.remoteID = did;		/* DID */
		icmd->ulpCommand = CMD_ELS_REQUEST64_CR;
		if (elscmd == ELS_CMD_FLOGI)
			icmd->ulpTimeout = FF_DEF_RATOV * 2;
		else
			icmd->ulpTimeout = phba->fc_ratov * 2;
	} else {
		icmd->un.xseq64.bdl.addrHigh = putPaddrHigh(pbuflist->phys);
		icmd->un.xseq64.bdl.addrLow = putPaddrLow(pbuflist->phys);
		icmd->un.xseq64.bdl.bdeFlags = BUFF_TYPE_BLP_64;
		icmd->un.xseq64.bdl.bdeSize = sizeof(struct ulp_bde64);
		icmd->un.xseq64.xmit_els_remoteID = did;	/* DID */
		icmd->ulpCommand = CMD_XMIT_ELS_RSP64_CX;
	}
	icmd->ulpBdeCount = 1;
	icmd->ulpLe = 1;
	icmd->ulpClass = CLASS3;

	/*
	 * If we have NPIV enabled, we want to send ELS traffic by VPI.
	 * For SLI4, since the driver controls VPIs we also want to include
	 * all ELS pt2pt protocol traffic as well.
	 */
	if ((phba->sli3_options & LPFC_SLI3_NPIV_ENABLED) ||
		((phba->sli_rev == LPFC_SLI_REV4) &&
		    (vport->fc_flag & FC_PT2PT))) {

		if (expectRsp) {
			icmd->un.elsreq64.myID = vport->fc_myDID;

			/* For ELS_REQUEST64_CR, use the VPI by default */
			icmd->ulpContext = phba->vpi_ids[vport->vpi];
		}

		icmd->ulpCt_h = 0;
		/* The CT field must be 0=INVALID_RPI for the ECHO cmd */
		if (elscmd == ELS_CMD_ECHO)
			icmd->ulpCt_l = 0; /* context = invalid RPI */
		else
			icmd->ulpCt_l = 1; /* context = VPI */
	}

	bpl = (struct ulp_bde64 *) pbuflist->virt;
	bpl->addrLow = le32_to_cpu(putPaddrLow(pcmd->phys));
	bpl->addrHigh = le32_to_cpu(putPaddrHigh(pcmd->phys));
	bpl->tus.f.bdeSize = cmdSize;
	bpl->tus.f.bdeFlags = 0;
	bpl->tus.w = le32_to_cpu(bpl->tus.w);

	if (expectRsp) {
		bpl++;
		bpl->addrLow = le32_to_cpu(putPaddrLow(prsp->phys));
		bpl->addrHigh = le32_to_cpu(putPaddrHigh(prsp->phys));
		bpl->tus.f.bdeSize = FCELSSIZE;
		bpl->tus.f.bdeFlags = BUFF_TYPE_BDE_64;
		bpl->tus.w = le32_to_cpu(bpl->tus.w);
	}

	/* prevent preparing iocb with NULL ndlp reference */
	elsiocb->context1 = lpfc_nlp_get(ndlp);
	if (!elsiocb->context1)
		goto els_iocb_free_pbuf_exit;
	elsiocb->context2 = pcmd;
	elsiocb->context3 = pbuflist;
	elsiocb->retry = retry;
	elsiocb->vport = vport;
	elsiocb->drvrTimeout = (phba->fc_ratov << 1) + LPFC_DRVR_TIMEOUT;

	if (prsp) {
		list_add(&prsp->list, &pcmd->list);
	}
	if (expectRsp) {
		/* Xmit ELS command <elsCmd> to remote NPORT <did> */
		lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
				 "0116 Xmit ELS command x%x to remote "
				 "NPORT x%x I/O tag: x%x, port state:x%x"
				 " fc_flag:x%x\n",
				 elscmd, did, elsiocb->iotag,
				 vport->port_state,
				 vport->fc_flag);
	} else {
		/* Xmit ELS response <elsCmd> to remote NPORT <did> */
		lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
				 "0117 Xmit ELS response x%x to remote "
				 "NPORT x%x I/O tag: x%x, size: x%x "
				 "port_state x%x fc_flag x%x\n",
				 elscmd, ndlp->nlp_DID, elsiocb->iotag,
				 cmdSize, vport->port_state,
				 vport->fc_flag);
	}
	return elsiocb;

els_iocb_free_pbuf_exit:
	if (expectRsp)
		lpfc_mbuf_free(phba, prsp->virt, prsp->phys);
	kfree(pbuflist);

els_iocb_free_prsp_exit:
	lpfc_mbuf_free(phba, pcmd->virt, pcmd->phys);
	kfree(prsp);

els_iocb_free_pcmb_exit:
	kfree(pcmd);
	lpfc_sli_release_iocbq(phba, elsiocb);
	return NULL;
}