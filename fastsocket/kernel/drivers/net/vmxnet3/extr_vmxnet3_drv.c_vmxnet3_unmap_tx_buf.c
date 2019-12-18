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
struct vmxnet3_tx_buf_info {scalar_t__ map_type; int /*<<< orphan*/  len; int /*<<< orphan*/  dma_addr; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ VMXNET3_MAP_NONE ; 
 scalar_t__ VMXNET3_MAP_PAGE ; 
 scalar_t__ VMXNET3_MAP_SINGLE ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_unmap_tx_buf(struct vmxnet3_tx_buf_info *tbi,
		     struct pci_dev *pdev)
{
	if (tbi->map_type == VMXNET3_MAP_SINGLE)
		pci_unmap_single(pdev, tbi->dma_addr, tbi->len,
				 PCI_DMA_TODEVICE);
	else if (tbi->map_type == VMXNET3_MAP_PAGE)
		pci_unmap_page(pdev, tbi->dma_addr, tbi->len,
			       PCI_DMA_TODEVICE);
	else
		BUG_ON(tbi->map_type != VMXNET3_MAP_NONE);

	tbi->map_type = VMXNET3_MAP_NONE; /* to help debugging */
}