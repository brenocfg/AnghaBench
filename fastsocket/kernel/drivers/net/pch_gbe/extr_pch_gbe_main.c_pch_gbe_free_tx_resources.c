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
struct pci_dev {int dummy; } ;
struct pch_gbe_tx_ring {int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; int /*<<< orphan*/ * buffer_info; } ;
struct pch_gbe_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pch_gbe_clean_tx_ring (struct pch_gbe_adapter*,struct pch_gbe_tx_ring*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void pch_gbe_free_tx_resources(struct pch_gbe_adapter *adapter,
				struct pch_gbe_tx_ring *tx_ring)
{
	struct pci_dev *pdev = adapter->pdev;

	pch_gbe_clean_tx_ring(adapter, tx_ring);
	vfree(tx_ring->buffer_info);
	tx_ring->buffer_info = NULL;
	pci_free_consistent(pdev, tx_ring->size, tx_ring->desc, tx_ring->dma);
	tx_ring->desc = NULL;
}