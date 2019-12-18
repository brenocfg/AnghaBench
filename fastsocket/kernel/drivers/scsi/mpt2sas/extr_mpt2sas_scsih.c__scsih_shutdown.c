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
struct workqueue_struct {int dummy; } ;
struct pci_dev {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct MPT2SAS_ADAPTER {int remove_host; int /*<<< orphan*/  fw_event_lock; struct workqueue_struct* firmware_event_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  _scsih_fw_event_cleanup_queue (struct MPT2SAS_ADAPTER*) ; 
 int /*<<< orphan*/  _scsih_ir_shutdown (struct MPT2SAS_ADAPTER*) ; 
 int /*<<< orphan*/  destroy_workqueue (struct workqueue_struct*) ; 
 int /*<<< orphan*/  mpt2sas_base_detach (struct MPT2SAS_ADAPTER*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 struct MPT2SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
_scsih_shutdown(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct MPT2SAS_ADAPTER *ioc = shost_priv(shost);
	struct workqueue_struct	*wq;
	unsigned long flags;

	ioc->remove_host = 1;
	_scsih_fw_event_cleanup_queue(ioc);

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	wq = ioc->firmware_event_thread;
	ioc->firmware_event_thread = NULL;
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
	if (wq)
		destroy_workqueue(wq);

	_scsih_ir_shutdown(ioc);
	mpt2sas_base_detach(ioc);
}