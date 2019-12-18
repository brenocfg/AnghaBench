#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lpfc_vport {int /*<<< orphan*/  vpi_state; int /*<<< orphan*/  fc_flag; int /*<<< orphan*/  port_state; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_hba {int sli3_options; int max_vports; scalar_t__ sli_rev; struct lpfc_vport* pport; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_VPORT_NEEDS_INIT_VPI ; 
 int /*<<< orphan*/  Fabric_DID ; 
 int LPFC_SLI3_NPIV_ENABLED ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  LPFC_VPI_REGISTERED ; 
 int /*<<< orphan*/  LPFC_VPORT_UNKNOWN ; 
 int /*<<< orphan*/  lpfc_cancel_retry_delay_tmo (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_cleanup_pending_mbox (struct lpfc_vport*) ; 
 struct lpfc_vport** lpfc_create_vport_work_array (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_destroy_vport_work_array (struct lpfc_hba*,struct lpfc_vport**) ; 
 int /*<<< orphan*/  lpfc_els_flush_all_cmd (struct lpfc_hba*) ; 
 scalar_t__ lpfc_fcf_inuse (struct lpfc_hba*) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int lpfc_issue_unreg_vfi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_mbx_unreg_vpi (struct lpfc_vport*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_sli4_unreg_all_rpis (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_unreg_hba_rpis (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

int
lpfc_unregister_fcf_prep(struct lpfc_hba *phba)
{
	struct lpfc_vport **vports;
	struct lpfc_nodelist *ndlp;
	struct Scsi_Host *shost;
	int i = 0, rc;

	/* Unregister RPIs */
	if (lpfc_fcf_inuse(phba))
		lpfc_unreg_hba_rpis(phba);

	/* At this point, all discovery is aborted */
	phba->pport->port_state = LPFC_VPORT_UNKNOWN;

	/* Unregister VPIs */
	vports = lpfc_create_vport_work_array(phba);
	if (vports && (phba->sli3_options & LPFC_SLI3_NPIV_ENABLED))
		for (i = 0; i <= phba->max_vports && vports[i] != NULL; i++) {
			/* Stop FLOGI/FDISC retries */
			ndlp = lpfc_findnode_did(vports[i], Fabric_DID);
			if (ndlp)
				lpfc_cancel_retry_delay_tmo(vports[i], ndlp);
			lpfc_cleanup_pending_mbox(vports[i]);
			if (phba->sli_rev == LPFC_SLI_REV4)
				lpfc_sli4_unreg_all_rpis(vports[i]);
			lpfc_mbx_unreg_vpi(vports[i]);
			shost = lpfc_shost_from_vport(vports[i]);
			spin_lock_irq(shost->host_lock);
			vports[i]->fc_flag |= FC_VPORT_NEEDS_INIT_VPI;
			vports[i]->vpi_state &= ~LPFC_VPI_REGISTERED;
			spin_unlock_irq(shost->host_lock);
		}
	lpfc_destroy_vport_work_array(phba, vports);
	if (i == 0 && (!(phba->sli3_options & LPFC_SLI3_NPIV_ENABLED))) {
		ndlp = lpfc_findnode_did(phba->pport, Fabric_DID);
		if (ndlp)
			lpfc_cancel_retry_delay_tmo(phba->pport, ndlp);
		lpfc_cleanup_pending_mbox(phba->pport);
		if (phba->sli_rev == LPFC_SLI_REV4)
			lpfc_sli4_unreg_all_rpis(phba->pport);
		lpfc_mbx_unreg_vpi(phba->pport);
		shost = lpfc_shost_from_vport(phba->pport);
		spin_lock_irq(shost->host_lock);
		phba->pport->fc_flag |= FC_VPORT_NEEDS_INIT_VPI;
		phba->pport->vpi_state &= ~LPFC_VPI_REGISTERED;
		spin_unlock_irq(shost->host_lock);
	}

	/* Cleanup any outstanding ELS commands */
	lpfc_els_flush_all_cmd(phba);

	/* Unregister the physical port VFI */
	rc = lpfc_issue_unreg_vfi(phba->pport);
	return rc;
}