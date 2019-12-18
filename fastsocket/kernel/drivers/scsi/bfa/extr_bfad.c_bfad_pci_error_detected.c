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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc; } ;
struct bfad_s {int bfad_flags; int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  hal_tmo; int /*<<< orphan*/  comp; int /*<<< orphan*/  bfa_fcs; TYPE_1__ bfa; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  int pci_channel_state_t ;

/* Variables and functions */
 int BFAD_EEH_BUSY ; 
 int BFAD_EEH_PCI_CHANNEL_IO_PERM_FAILURE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_CAN_RECOVER ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_fcs_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_ioc_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfad_remove_intr (struct bfad_s*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
#define  pci_channel_io_frozen 130 
#define  pci_channel_io_normal 129 
#define  pci_channel_io_perm_failure 128 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct bfad_s* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pci_ers_result_t
bfad_pci_error_detected(struct pci_dev *pdev, pci_channel_state_t state)
{
	struct bfad_s *bfad = pci_get_drvdata(pdev);
	unsigned long	flags;
	pci_ers_result_t ret = PCI_ERS_RESULT_NONE;

	dev_printk(KERN_ERR, &pdev->dev,
		   "error detected state: %d - flags: 0x%x\n",
		   state, bfad->bfad_flags);

	switch (state) {
	case pci_channel_io_normal: /* non-fatal error */
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfad_flags &= ~BFAD_EEH_BUSY;
		/* Suspend/fail all bfa operations */
		bfa_ioc_suspend(&bfad->bfa.ioc);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		del_timer_sync(&bfad->hal_tmo);
		ret = PCI_ERS_RESULT_CAN_RECOVER;
		break;
	case pci_channel_io_frozen: /* fatal error */
		init_completion(&bfad->comp);
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfad_flags |= BFAD_EEH_BUSY;
		/* Suspend/fail all bfa operations */
		bfa_ioc_suspend(&bfad->bfa.ioc);
		bfa_fcs_stop(&bfad->bfa_fcs);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		wait_for_completion(&bfad->comp);

		bfad_remove_intr(bfad);
		del_timer_sync(&bfad->hal_tmo);
		pci_disable_device(pdev);
		ret = PCI_ERS_RESULT_NEED_RESET;
		break;
	case pci_channel_io_perm_failure: /* PCI Card is DEAD */
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfad_flags |= BFAD_EEH_BUSY |
				    BFAD_EEH_PCI_CHANNEL_IO_PERM_FAILURE;
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);

		/* If the error_detected handler is called with the reason
		 * pci_channel_io_perm_failure - it will subsequently call
		 * pci_remove() entry point to remove the pci device from the
		 * system - So defer the cleanup to pci_remove(); cleaning up
		 * here causes inconsistent state during pci_remove().
		 */
		ret = PCI_ERS_RESULT_DISCONNECT;
		break;
	default:
		WARN_ON(1);
	}

	return ret;
}