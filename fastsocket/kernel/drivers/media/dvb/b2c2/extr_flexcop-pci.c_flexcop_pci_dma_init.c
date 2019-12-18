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
struct flexcop_pci {int /*<<< orphan*/  init_state; int /*<<< orphan*/  fc_dev; int /*<<< orphan*/ * dma; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_DEFAULT_DMA1_BUFSIZE ; 
 int /*<<< orphan*/  FC_DEFAULT_DMA2_BUFSIZE ; 
 int /*<<< orphan*/  FC_PCI_DMA_INIT ; 
 int FC_SRAM_DEST_CAI ; 
 int FC_SRAM_DEST_CAO ; 
 int FC_SRAM_DEST_MEDIA ; 
 int FC_SRAM_DEST_NET ; 
 int /*<<< orphan*/  FC_SRAM_DEST_TARGET_DMA1 ; 
 int /*<<< orphan*/  FC_SRAM_DEST_TARGET_DMA2 ; 
 int flexcop_dma_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flexcop_dma_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flexcop_sram_set_dest (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flexcop_pci_dma_init(struct flexcop_pci *fc_pci)
{
	int ret;
	ret = flexcop_dma_allocate(fc_pci->pdev, &fc_pci->dma[0],
			FC_DEFAULT_DMA1_BUFSIZE);
	if (ret != 0)
		return ret;

	ret = flexcop_dma_allocate(fc_pci->pdev, &fc_pci->dma[1],
			FC_DEFAULT_DMA2_BUFSIZE);
	if (ret != 0) {
		flexcop_dma_free(&fc_pci->dma[0]);
		return ret;
	}

	flexcop_sram_set_dest(fc_pci->fc_dev, FC_SRAM_DEST_MEDIA |
			FC_SRAM_DEST_NET, FC_SRAM_DEST_TARGET_DMA1);
	flexcop_sram_set_dest(fc_pci->fc_dev, FC_SRAM_DEST_CAO |
			FC_SRAM_DEST_CAI, FC_SRAM_DEST_TARGET_DMA2);
	fc_pci->init_state |= FC_PCI_DMA_INIT;
	return ret;
}