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
struct lpfc_vport {int fc_flag; int /*<<< orphan*/  port_state; scalar_t__ num_disc_nodes; scalar_t__ fc_npr_cnt; int /*<<< orphan*/  vpi_state; int /*<<< orphan*/  fc_myDID; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_7__ {int mbxStatus; } ;
struct TYPE_6__ {TYPE_2__ mb; } ;
struct TYPE_8__ {TYPE_1__ u; struct lpfc_vport* vport; } ;
typedef  TYPE_2__ MAILBOX_t ;
typedef  TYPE_3__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FC_FABRIC ; 
 int FC_NDISC_ACTIVE ; 
 int FC_PUBLIC_LOOP ; 
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int FC_VPORT_NEEDS_REG_VPI ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NODE ; 
 int /*<<< orphan*/  LPFC_VPI_REGISTERED ; 
 int /*<<< orphan*/  LPFC_VPORT_READY ; 
 int /*<<< orphan*/  lpfc_can_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_disc_plogi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_mbx_cmpl_reg_vpi(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	struct lpfc_vport *vport = pmb->vport;
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);
	MAILBOX_t *mb = &pmb->u.mb;

	switch (mb->mbxStatus) {
	case 0x0011:
	case 0x9601:
	case 0x9602:
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NODE,
				 "0912 cmpl_reg_vpi, mb status = 0x%x\n",
				 mb->mbxStatus);
		lpfc_vport_set_state(vport, FC_VPORT_FAILED);
		spin_lock_irq(shost->host_lock);
		vport->fc_flag &= ~(FC_FABRIC | FC_PUBLIC_LOOP);
		spin_unlock_irq(shost->host_lock);
		vport->fc_myDID = 0;
		goto out;
	}

	spin_lock_irq(shost->host_lock);
	vport->vpi_state |= LPFC_VPI_REGISTERED;
	vport->fc_flag &= ~FC_VPORT_NEEDS_REG_VPI;
	spin_unlock_irq(shost->host_lock);
	vport->num_disc_nodes = 0;
	/* go thru NPR list and issue ELS PLOGIs */
	if (vport->fc_npr_cnt)
		lpfc_els_disc_plogi(vport);

	if (!vport->num_disc_nodes) {
		spin_lock_irq(shost->host_lock);
		vport->fc_flag &= ~FC_NDISC_ACTIVE;
		spin_unlock_irq(shost->host_lock);
		lpfc_can_disctmo(vport);
	}
	vport->port_state = LPFC_VPORT_READY;

out:
	mempool_free(pmb, phba->mbox_mem_pool);
	return;
}