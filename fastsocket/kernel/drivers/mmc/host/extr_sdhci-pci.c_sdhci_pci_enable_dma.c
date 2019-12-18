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
struct sdhci_pci_slot {TYPE_1__* chip; } ;
struct sdhci_host {int flags; } ;
struct pci_dev {int class; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int PCI_CLASS_SYSTEM_SDHCI ; 
 int PCI_SDHCI_IFDMA ; 
 int SDHCI_USE_SDMA ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 struct sdhci_pci_slot* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static int sdhci_pci_enable_dma(struct sdhci_host *host)
{
	struct sdhci_pci_slot *slot;
	struct pci_dev *pdev;
	int ret;

	slot = sdhci_priv(host);
	pdev = slot->chip->pdev;

	if (((pdev->class & 0xFFFF00) == (PCI_CLASS_SYSTEM_SDHCI << 8)) &&
		((pdev->class & 0x0000FF) != PCI_SDHCI_IFDMA) &&
		(host->flags & SDHCI_USE_SDMA)) {
		dev_warn(&pdev->dev, "Will use DMA mode even though HW "
			"doesn't fully claim to support it.\n");
	}

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	pci_set_master(pdev);

	return 0;
}