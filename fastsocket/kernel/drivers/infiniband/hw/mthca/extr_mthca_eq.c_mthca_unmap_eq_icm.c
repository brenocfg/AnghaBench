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
struct TYPE_2__ {int /*<<< orphan*/  icm_page; int /*<<< orphan*/  icm_dma; int /*<<< orphan*/  icm_virt; } ;
struct mthca_dev {TYPE_1__ eq_table; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_UNMAP_ICM (struct mthca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mthca_unmap_eq_icm(struct mthca_dev *dev)
{
	mthca_UNMAP_ICM(dev, dev->eq_table.icm_virt, 1);
	pci_unmap_page(dev->pdev, dev->eq_table.icm_dma, PAGE_SIZE,
		       PCI_DMA_BIDIRECTIONAL);
	__free_page(dev->eq_table.icm_page);
}