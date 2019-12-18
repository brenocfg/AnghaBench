#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int load_flag; int /*<<< orphan*/  unreg_vpi_cmpl; int /*<<< orphan*/  fc_flag; int /*<<< orphan*/  vpi_state; int /*<<< orphan*/  vpi; } ;
struct lpfc_hba {struct lpfc_vport* pport; int /*<<< orphan*/  mbox_mem_pool; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_7__ {int mbxStatus; } ;
struct TYPE_6__ {TYPE_2__ mb; } ;
struct TYPE_8__ {struct lpfc_vport* vport; TYPE_1__ u; } ;
typedef  TYPE_2__ MAILBOX_t ;
typedef  TYPE_3__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FC_UNLOADING ; 
 int /*<<< orphan*/  FC_VPORT_NEEDS_REG_VPI ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NODE ; 
 int /*<<< orphan*/  LPFC_EVT_RESET_HBA ; 
 int /*<<< orphan*/  LPFC_VPI_REGISTERED ; 
 int /*<<< orphan*/  VPORT_OK ; 
 int /*<<< orphan*/  lpfc_cleanup_vports_rrqs (struct lpfc_vport*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_workq_post_event (struct lpfc_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_mbx_cmpl_unreg_vpi(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	MAILBOX_t *mb = &pmb->u.mb;
	struct lpfc_vport *vport = pmb->vport;
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);

	switch (mb->mbxStatus) {
	case 0x0011:
	case 0x0020:
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NODE,
				 "0911 cmpl_unreg_vpi, mb status = 0x%x\n",
				 mb->mbxStatus);
		break;
	/* If VPI is busy, reset the HBA */
	case 0x9700:
		lpfc_printf_vlog(vport, KERN_ERR, LOG_NODE,
			"2798 Unreg_vpi failed vpi 0x%x, mb status = 0x%x\n",
			vport->vpi, mb->mbxStatus);
		if (!(phba->pport->load_flag & FC_UNLOADING))
			lpfc_workq_post_event(phba, NULL, NULL,
				LPFC_EVT_RESET_HBA);
	}
	spin_lock_irq(shost->host_lock);
	vport->vpi_state &= ~LPFC_VPI_REGISTERED;
	vport->fc_flag |= FC_VPORT_NEEDS_REG_VPI;
	spin_unlock_irq(shost->host_lock);
	vport->unreg_vpi_cmpl = VPORT_OK;
	mempool_free(pmb, phba->mbox_mem_pool);
	lpfc_cleanup_vports_rrqs(vport, NULL);
	/*
	 * This shost reference might have been taken at the beginning of
	 * lpfc_vport_delete()
	 */
	if ((vport->load_flag & FC_UNLOADING) && (vport != phba->pport))
		scsi_host_put(shost);
}