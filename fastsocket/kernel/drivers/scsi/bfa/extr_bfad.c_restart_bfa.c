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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bfad_s {int bfad_flags; int /*<<< orphan*/  comp; int /*<<< orphan*/  pci_name; int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; int /*<<< orphan*/  hal_pcidev; int /*<<< orphan*/  meminfo; int /*<<< orphan*/  ioc_cfg; struct pci_dev* pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_E_INTR_INIT_FAILED ; 
 int BFAD_MSIX_ON ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  bfa_attach (int /*<<< orphan*/ *,struct bfad_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_iocfc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfad_drv_start (struct bfad_s*) ; 
 int /*<<< orphan*/  bfad_init_timer (struct bfad_s*) ; 
 scalar_t__ bfad_install_msix_handler (struct bfad_s*) ; 
 scalar_t__ bfad_setup_intr (struct bfad_s*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
restart_bfa(struct bfad_s *bfad)
{
	unsigned long flags;
	struct pci_dev *pdev = bfad->pcidev;

	bfa_attach(&bfad->bfa, bfad, &bfad->ioc_cfg,
		   &bfad->meminfo, &bfad->hal_pcidev);

	/* Enable Interrupt and wait bfa_init completion */
	if (bfad_setup_intr(bfad)) {
		dev_printk(KERN_WARNING, &pdev->dev,
			   "%s: bfad_setup_intr failed\n", bfad->pci_name);
		bfa_sm_send_event(bfad, BFAD_E_INTR_INIT_FAILED);
		return -1;
	}

	init_completion(&bfad->comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_iocfc_init(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	/* Set up interrupt handler for each vectors */
	if ((bfad->bfad_flags & BFAD_MSIX_ON) &&
	    bfad_install_msix_handler(bfad))
		dev_printk(KERN_WARNING, &pdev->dev,
			   "%s: install_msix failed.\n", bfad->pci_name);

	bfad_init_timer(bfad);
	wait_for_completion(&bfad->comp);
	bfad_drv_start(bfad);

	return 0;
}