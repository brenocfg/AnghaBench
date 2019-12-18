#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int /*<<< orphan*/  fc_flag; struct lpfc_hba* phba; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; TYPE_1__* pport; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  mbox_cmpl; struct lpfc_vport* vport; } ;
struct TYPE_7__ {int /*<<< orphan*/  port_state; } ;
typedef  TYPE_2__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FC_VFI_REGISTERED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int LOG_DISCOVERY ; 
 int LOG_MBOX ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,int,...) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_unreg_vfi (TYPE_2__*,struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_unregister_vfi_cmpl ; 
 TYPE_2__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

int
lpfc_issue_unreg_vfi(struct lpfc_vport *vport)
{
	struct lpfc_hba *phba = vport->phba;
	struct Scsi_Host *shost;
	LPFC_MBOXQ_t *mboxq;
	int rc;

	mboxq = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mboxq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_DISCOVERY|LOG_MBOX,
				"2556 UNREG_VFI mbox allocation failed"
				"HBA state x%x\n", phba->pport->port_state);
		return -ENOMEM;
	}

	lpfc_unreg_vfi(mboxq, vport);
	mboxq->vport = vport;
	mboxq->mbox_cmpl = lpfc_unregister_vfi_cmpl;

	rc = lpfc_sli_issue_mbox(phba, mboxq, MBX_NOWAIT);
	if (rc == MBX_NOT_FINISHED) {
		lpfc_printf_log(phba, KERN_ERR, LOG_DISCOVERY|LOG_MBOX,
				"2557 UNREG_VFI issue mbox failed rc x%x "
				"HBA state x%x\n",
				rc, phba->pport->port_state);
		mempool_free(mboxq, phba->mbox_mem_pool);
		return -EIO;
	}

	shost = lpfc_shost_from_vport(vport);
	spin_lock_irq(shost->host_lock);
	vport->fc_flag &= ~FC_VFI_REGISTERED;
	spin_unlock_irq(shost->host_lock);
	return 0;
}