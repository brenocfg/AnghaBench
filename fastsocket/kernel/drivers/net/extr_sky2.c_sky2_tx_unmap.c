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
struct tx_ring_info {int flags; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_MAP_PAGE ; 
 int TX_MAP_SINGLE ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  pci_unmap_addr (struct tx_ring_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_len (struct tx_ring_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_tx_unmap(struct pci_dev *pdev, struct tx_ring_info *re)
{
	if (re->flags & TX_MAP_SINGLE)
		pci_unmap_single(pdev, pci_unmap_addr(re, mapaddr),
				 pci_unmap_len(re, maplen),
				 PCI_DMA_TODEVICE);
	else if (re->flags & TX_MAP_PAGE)
		pci_unmap_page(pdev, pci_unmap_addr(re, mapaddr),
			       pci_unmap_len(re, maplen),
			       PCI_DMA_TODEVICE);
	re->flags = 0;
}