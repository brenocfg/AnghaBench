#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct TYPE_4__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct lpfc_hba {int /*<<< orphan*/  slim_memmap_p; int /*<<< orphan*/  ctrl_regs_memmap_p; TYPE_1__ slim2p; TYPE_2__ hbqslimp; struct pci_dev* pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLI2_SLIM_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_hbq_size () ; 

__attribute__((used)) static void
lpfc_sli_pci_mem_unset(struct lpfc_hba *phba)
{
	struct pci_dev *pdev;

	/* Obtain PCI device reference */
	if (!phba->pcidev)
		return;
	else
		pdev = phba->pcidev;

	/* Free coherent DMA memory allocated */
	dma_free_coherent(&pdev->dev, lpfc_sli_hbq_size(),
			  phba->hbqslimp.virt, phba->hbqslimp.phys);
	dma_free_coherent(&pdev->dev, SLI2_SLIM_SIZE,
			  phba->slim2p.virt, phba->slim2p.phys);

	/* I/O memory unmap */
	iounmap(phba->ctrl_regs_memmap_p);
	iounmap(phba->slim_memmap_p);

	return;
}