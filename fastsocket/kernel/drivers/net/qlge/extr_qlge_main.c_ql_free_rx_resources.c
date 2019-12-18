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
struct rx_ring {int /*<<< orphan*/ * cq_base; int /*<<< orphan*/  cq_base_dma; int /*<<< orphan*/  cq_size; int /*<<< orphan*/ * lbq; int /*<<< orphan*/ * lbq_base; int /*<<< orphan*/  lbq_base_dma; int /*<<< orphan*/  lbq_size; int /*<<< orphan*/ * sbq; int /*<<< orphan*/ * sbq_base; int /*<<< orphan*/  sbq_base_dma; int /*<<< orphan*/  sbq_size; } ;
struct ql_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ql_free_rx_resources(struct ql_adapter *qdev,
				 struct rx_ring *rx_ring)
{
	/* Free the small buffer queue. */
	if (rx_ring->sbq_base) {
		pci_free_consistent(qdev->pdev,
				    rx_ring->sbq_size,
				    rx_ring->sbq_base, rx_ring->sbq_base_dma);
		rx_ring->sbq_base = NULL;
	}

	/* Free the small buffer queue control blocks. */
	kfree(rx_ring->sbq);
	rx_ring->sbq = NULL;

	/* Free the large buffer queue. */
	if (rx_ring->lbq_base) {
		pci_free_consistent(qdev->pdev,
				    rx_ring->lbq_size,
				    rx_ring->lbq_base, rx_ring->lbq_base_dma);
		rx_ring->lbq_base = NULL;
	}

	/* Free the large buffer queue control blocks. */
	kfree(rx_ring->lbq);
	rx_ring->lbq = NULL;

	/* Free the rx queue. */
	if (rx_ring->cq_base) {
		pci_free_consistent(qdev->pdev,
				    rx_ring->cq_size,
				    rx_ring->cq_base, rx_ring->cq_base_dma);
		rx_ring->cq_base = NULL;
	}
}