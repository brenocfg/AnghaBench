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
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ixgbevf_rx_buffer {int dummy; } ;
struct ixgbevf_ring {int count; int size; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/ * rx_buffer_info; int /*<<< orphan*/  desc; int /*<<< orphan*/  dma; } ;
struct ixgbevf_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int) ; 

int ixgbevf_setup_rx_resources(struct ixgbevf_adapter *adapter,
			       struct ixgbevf_ring *rx_ring)
{
	struct pci_dev *pdev = adapter->pdev;
	int size;

	size = sizeof(struct ixgbevf_rx_buffer) * rx_ring->count;
	rx_ring->rx_buffer_info = vzalloc(size);
	if (!rx_ring->rx_buffer_info)
		goto alloc_failed;

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * sizeof(union ixgbe_adv_rx_desc);
	rx_ring->size = ALIGN(rx_ring->size, 4096);

	rx_ring->desc = dma_alloc_coherent(&pdev->dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);

	if (!rx_ring->desc) {
		vfree(rx_ring->rx_buffer_info);
		rx_ring->rx_buffer_info = NULL;
		goto alloc_failed;
	}

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	return 0;
alloc_failed:
	return -ENOMEM;
}