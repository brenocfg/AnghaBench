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
struct pci_dev {int /*<<< orphan*/  dma_mask; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int PCI_DMA_NONE ; 
 int pci_dac_dma_supported (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single_1 (struct pci_dev*,void*,size_t,int) ; 

dma_addr_t
pci_map_single(struct pci_dev *pdev, void *cpu_addr, size_t size, int dir)
{
	int dac_allowed; 

	if (dir == PCI_DMA_NONE)
		BUG();

	dac_allowed = pdev ? pci_dac_dma_supported(pdev, pdev->dma_mask) : 0; 
	return pci_map_single_1(pdev, cpu_addr, size, dac_allowed);
}