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
struct pci_dev {int dummy; } ;
struct ata_host {int /*<<< orphan*/ * iomap; TYPE_1__** ports; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DMA_MASK ; 
 size_t SCC_BMID_BAR ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int scc_reset_controller (struct ata_host*) ; 
 int /*<<< orphan*/  scc_setup_ports (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scc_host_init(struct ata_host *host)
{
	struct pci_dev *pdev = to_pci_dev(host->dev);
	int rc;

	rc = scc_reset_controller(host);
	if (rc)
		return rc;

	rc = pci_set_dma_mask(pdev, ATA_DMA_MASK);
	if (rc)
		return rc;
	rc = pci_set_consistent_dma_mask(pdev, ATA_DMA_MASK);
	if (rc)
		return rc;

	scc_setup_ports(&host->ports[0]->ioaddr, host->iomap[SCC_BMID_BAR]);

	pci_set_master(pdev);

	return 0;
}