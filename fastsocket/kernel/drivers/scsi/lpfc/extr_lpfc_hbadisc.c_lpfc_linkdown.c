#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int fc_flag; scalar_t__ fc_myDID; } ;
struct TYPE_8__ {int fcf_flag; } ;
struct lpfc_hba {scalar_t__ link_state; int max_vports; struct lpfc_vport* pport; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  hbalock; TYPE_1__ fcf; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; } ;
struct TYPE_9__ {struct lpfc_vport* vport; void* mbox_cmpl; } ;
typedef  TYPE_2__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FCF_AVAILABLE ; 
 int FCF_SCAN_DONE ; 
 int FC_LBIT ; 
 int FC_PT2PT ; 
 int FC_PT2PT_PLOGI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LPFC_LINK_DOWN ; 
 int /*<<< orphan*/  LPFC_UNREG_ALL_DFLT_RPIS ; 
 scalar_t__ MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  lpfc_config_link (struct lpfc_hba*,TYPE_2__*) ; 
 struct lpfc_vport** lpfc_create_vport_work_array (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_destroy_vport_work_array (struct lpfc_hba*,struct lpfc_vport**) ; 
 int /*<<< orphan*/  lpfc_linkdown_port (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_scsi_dev_block (struct lpfc_hba*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 void* lpfc_sli_def_mbox_cmpl ; 
 scalar_t__ lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_unreg_did (struct lpfc_hba*,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
lpfc_linkdown(struct lpfc_hba *phba)
{
	struct lpfc_vport *vport = phba->pport;
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);
	struct lpfc_vport **vports;
	LPFC_MBOXQ_t          *mb;
	int i;

	if (phba->link_state == LPFC_LINK_DOWN)
		return 0;

	/* Block all SCSI stack I/Os */
	lpfc_scsi_dev_block(phba);

	spin_lock_irq(&phba->hbalock);
	phba->fcf.fcf_flag &= ~(FCF_AVAILABLE | FCF_SCAN_DONE);
	spin_unlock_irq(&phba->hbalock);
	if (phba->link_state > LPFC_LINK_DOWN) {
		phba->link_state = LPFC_LINK_DOWN;
		spin_lock_irq(shost->host_lock);
		phba->pport->fc_flag &= ~FC_LBIT;
		spin_unlock_irq(shost->host_lock);
	}
	vports = lpfc_create_vport_work_array(phba);
	if (vports != NULL)
		for (i = 0; i <= phba->max_vports && vports[i] != NULL; i++) {
			/* Issue a LINK DOWN event to all nodes */
			lpfc_linkdown_port(vports[i]);
		}
	lpfc_destroy_vport_work_array(phba, vports);
	/* Clean up any firmware default rpi's */
	mb = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (mb) {
		lpfc_unreg_did(phba, 0xffff, LPFC_UNREG_ALL_DFLT_RPIS, mb);
		mb->vport = vport;
		mb->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
		if (lpfc_sli_issue_mbox(phba, mb, MBX_NOWAIT)
		    == MBX_NOT_FINISHED) {
			mempool_free(mb, phba->mbox_mem_pool);
		}
	}

	/* Setup myDID for link up if we are in pt2pt mode */
	if (phba->pport->fc_flag & FC_PT2PT) {
		phba->pport->fc_myDID = 0;
		mb = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
		if (mb) {
			lpfc_config_link(phba, mb);
			mb->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
			mb->vport = vport;
			if (lpfc_sli_issue_mbox(phba, mb, MBX_NOWAIT)
			    == MBX_NOT_FINISHED) {
				mempool_free(mb, phba->mbox_mem_pool);
			}
		}
		spin_lock_irq(shost->host_lock);
		phba->pport->fc_flag &= ~(FC_PT2PT | FC_PT2PT_PLOGI);
		spin_unlock_irq(shost->host_lock);
	}

	return 0;
}