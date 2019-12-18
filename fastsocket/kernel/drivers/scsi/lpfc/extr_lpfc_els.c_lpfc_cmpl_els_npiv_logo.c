#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int /*<<< orphan*/  fc_flag; int /*<<< orphan*/  num_disc_nodes; int /*<<< orphan*/  unreg_vpi_cmpl; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; } ;
struct TYPE_4__ {int /*<<< orphan*/  remoteID; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ulpWord; TYPE_1__ rcvels; } ;
struct TYPE_6__ {scalar_t__ ulpStatus; int /*<<< orphan*/  ulpTimeout; TYPE_2__ un; } ;
struct lpfc_iocbq {TYPE_3__ iocb; scalar_t__ context1; struct lpfc_vport* vport; } ;
struct lpfc_hba {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
typedef  TYPE_3__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  FC_FABRIC ; 
 scalar_t__ IOSTAT_SUCCESS ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_CMD ; 
 int /*<<< orphan*/  VPORT_ERROR ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_els_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_cmpl_els_npiv_logo(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
			struct lpfc_iocbq *rspiocb)
{
	struct lpfc_vport *vport = cmdiocb->vport;
	IOCB_t *irsp;
	struct lpfc_nodelist *ndlp;
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);

	ndlp = (struct lpfc_nodelist *)cmdiocb->context1;
	irsp = &rspiocb->iocb;
	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_CMD,
		"LOGO npiv cmpl:  status:x%x/x%x did:x%x",
		irsp->ulpStatus, irsp->un.ulpWord[4], irsp->un.rcvels.remoteID);

	lpfc_els_free_iocb(phba, cmdiocb);
	vport->unreg_vpi_cmpl = VPORT_ERROR;

	/* Trigger the release of the ndlp after logo */
	lpfc_nlp_put(ndlp);

	/* NPIV LOGO completes to NPort <nlp_DID> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "2928 NPIV LOGO completes to NPort x%x "
			 "Data: x%x x%x x%x x%x\n",
			 ndlp->nlp_DID, irsp->ulpStatus, irsp->un.ulpWord[4],
			 irsp->ulpTimeout, vport->num_disc_nodes);

	if (irsp->ulpStatus == IOSTAT_SUCCESS) {
		spin_lock_irq(shost->host_lock);
		vport->fc_flag &= ~FC_FABRIC;
		spin_unlock_irq(shost->host_lock);
	}
}