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
typedef  int uint32_t ;
struct lpfc_vport {int /*<<< orphan*/  fc_nodename; int /*<<< orphan*/  fc_portname; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; scalar_t__ nlp_prev_state; int /*<<< orphan*/  nlp_DID; } ;
struct lpfc_name {int dummy; } ;
struct TYPE_5__ {int remoteID; } ;
struct TYPE_6__ {TYPE_1__ elsreq64; } ;
struct TYPE_7__ {TYPE_2__ un; } ;
struct lpfc_iocbq {scalar_t__ context2; TYPE_3__ iocb; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct TYPE_8__ {int Mflags; int Rflags; int /*<<< orphan*/  RnodeName; int /*<<< orphan*/  RportName; } ;
typedef  TYPE_3__ IOCB_t ;
typedef  TYPE_4__ FARP ;

/* Variables and functions */
 int FARP_MATCH_NODE ; 
 int FARP_MATCH_PORT ; 
 int FARP_REQUEST_FARPR ; 
 int FARP_REQUEST_PLOGI ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 scalar_t__ NLP_STE_MAPPED_NODE ; 
 int /*<<< orphan*/  NLP_STE_PLOGI_ISSUE ; 
 scalar_t__ NLP_STE_UNMAPPED_NODE ; 
 int /*<<< orphan*/  lpfc_issue_els_farpr (struct lpfc_vport*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_issue_els_plogi (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lpfc_els_rcv_farp(struct lpfc_vport *vport, struct lpfc_iocbq *cmdiocb,
		  struct lpfc_nodelist *ndlp)
{
	struct lpfc_dmabuf *pcmd;
	uint32_t *lp;
	IOCB_t *icmd;
	FARP *fp;
	uint32_t cmd, cnt, did;

	icmd = &cmdiocb->iocb;
	did = icmd->un.elsreq64.remoteID;
	pcmd = (struct lpfc_dmabuf *) cmdiocb->context2;
	lp = (uint32_t *) pcmd->virt;

	cmd = *lp++;
	fp = (FARP *) lp;
	/* FARP-REQ received from DID <did> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "0601 FARP-REQ received from DID x%x\n", did);
	/* We will only support match on WWPN or WWNN */
	if (fp->Mflags & ~(FARP_MATCH_NODE | FARP_MATCH_PORT)) {
		return 0;
	}

	cnt = 0;
	/* If this FARP command is searching for my portname */
	if (fp->Mflags & FARP_MATCH_PORT) {
		if (memcmp(&fp->RportName, &vport->fc_portname,
			   sizeof(struct lpfc_name)) == 0)
			cnt = 1;
	}

	/* If this FARP command is searching for my nodename */
	if (fp->Mflags & FARP_MATCH_NODE) {
		if (memcmp(&fp->RnodeName, &vport->fc_nodename,
			   sizeof(struct lpfc_name)) == 0)
			cnt = 1;
	}

	if (cnt) {
		if ((ndlp->nlp_state == NLP_STE_UNMAPPED_NODE) ||
		   (ndlp->nlp_state == NLP_STE_MAPPED_NODE)) {
			/* Log back into the node before sending the FARP. */
			if (fp->Rflags & FARP_REQUEST_PLOGI) {
				ndlp->nlp_prev_state = ndlp->nlp_state;
				lpfc_nlp_set_state(vport, ndlp,
						   NLP_STE_PLOGI_ISSUE);
				lpfc_issue_els_plogi(vport, ndlp->nlp_DID, 0);
			}

			/* Send a FARP response to that node */
			if (fp->Rflags & FARP_REQUEST_FARPR)
				lpfc_issue_els_farpr(vport, did, 0);
		}
	}
	return 0;
}