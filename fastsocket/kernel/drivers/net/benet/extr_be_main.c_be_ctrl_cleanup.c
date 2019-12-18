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
struct be_dma_mem {int /*<<< orphan*/  dma; scalar_t__ va; int /*<<< orphan*/  size; } ;
struct be_adapter {TYPE_1__* pdev; struct be_dma_mem rx_filter; struct be_dma_mem mbox_mem_alloced; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_unmap_pci_bars (struct be_adapter*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_ctrl_cleanup(struct be_adapter *adapter)
{
	struct be_dma_mem *mem = &adapter->mbox_mem_alloced;

	be_unmap_pci_bars(adapter);

	if (mem->va)
		dma_free_coherent(&adapter->pdev->dev, mem->size, mem->va,
				  mem->dma);

	mem = &adapter->rx_filter;
	if (mem->va)
		dma_free_coherent(&adapter->pdev->dev, mem->size, mem->va,
				  mem->dma);
}