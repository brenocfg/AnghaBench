#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct CommandControlBlock {scalar_t__ startdone; TYPE_1__* pcmd; } ;
struct AdapterControlBlock {struct CommandControlBlock** pccb_pool; int /*<<< orphan*/  ccboutstandingcount; int /*<<< orphan*/  acb_flags; int /*<<< orphan*/  eternal_timer; } ;
struct TYPE_2__ {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACB_F_IOP_INITED ; 
 int /*<<< orphan*/  ACB_F_SCSISTOPADAPTER ; 
 scalar_t__ ARCMSR_CCB_ABORTED ; 
 scalar_t__ ARCMSR_CCB_START ; 
 int ARCMSR_MAX_FREECCB_NUM ; 
 int ARCMSR_MAX_OUTSTANDING_CMD ; 
 int DID_ABORT ; 
 int /*<<< orphan*/  arcmsr_abort_allcmd (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_ccb_complete (struct CommandControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_disable_outbound_ints (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_done4abort_postqueue (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_flush_adapter_cache (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_free_ccb_pool (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_free_hbb_mu (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_free_sysfs_attr (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_interrupt (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_stop_adapter_bgrb (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_unmap_pciregion (struct AdapterControlBlock*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static void arcmsr_remove(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	struct AdapterControlBlock *acb =
		(struct AdapterControlBlock *) host->hostdata;
	int poll_count = 0;
	arcmsr_free_sysfs_attr(acb);
	scsi_remove_host(host);
	flush_scheduled_work();
	del_timer_sync(&acb->eternal_timer);
	arcmsr_disable_outbound_ints(acb);
	arcmsr_stop_adapter_bgrb(acb);
	arcmsr_flush_adapter_cache(acb);	
	acb->acb_flags |= ACB_F_SCSISTOPADAPTER;
	acb->acb_flags &= ~ACB_F_IOP_INITED;

	for (poll_count = 0; poll_count < ARCMSR_MAX_OUTSTANDING_CMD; poll_count++){
		if (!atomic_read(&acb->ccboutstandingcount))
			break;
		arcmsr_interrupt(acb);/* FIXME: need spinlock */
		msleep(25);
	}

	if (atomic_read(&acb->ccboutstandingcount)) {
		int i;

		arcmsr_abort_allcmd(acb);
		arcmsr_done4abort_postqueue(acb);
		for (i = 0; i < ARCMSR_MAX_FREECCB_NUM; i++) {
			struct CommandControlBlock *ccb = acb->pccb_pool[i];
			if (ccb->startdone == ARCMSR_CCB_START) {
				ccb->startdone = ARCMSR_CCB_ABORTED;
				ccb->pcmd->result = DID_ABORT << 16;
				arcmsr_ccb_complete(ccb);
			}
		}
	}
	free_irq(pdev->irq, acb);
	arcmsr_free_ccb_pool(acb);
	arcmsr_free_hbb_mu(acb);
	arcmsr_unmap_pciregion(acb);
	pci_release_regions(pdev);
	scsi_host_put(host);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
}