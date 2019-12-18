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
struct pch_gbe_rx_ring {int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; int /*<<< orphan*/ * buffer_info; } ;
struct pch_gbe_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pch_gbe_clean_rx_ring (struct pch_gbe_adapter*,struct pch_gbe_rx_ring*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void pch_gbe_free_rx_resources(struct pch_gbe_adapter *adapter,
				struct pch_gbe_rx_ring *rx_ring)
{
	struct pci_dev *pdev = adapter->pdev;

	pch_gbe_clean_rx_ring(adapter, rx_ring);
	vfree(rx_ring->buffer_info);
	rx_ring->buffer_info = NULL;
	pci_free_consistent(pdev, rx_ring->size, rx_ring->desc, rx_ring->dma);
	rx_ring->desc = NULL;
}