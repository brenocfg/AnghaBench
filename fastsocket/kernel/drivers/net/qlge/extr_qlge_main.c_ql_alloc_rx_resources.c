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
struct rx_ring {int sbq_len; int lbq_len; int /*<<< orphan*/ * lbq; int /*<<< orphan*/ * lbq_base; int /*<<< orphan*/  lbq_base_dma; int /*<<< orphan*/  lbq_size; int /*<<< orphan*/ * sbq; int /*<<< orphan*/ * sbq_base; int /*<<< orphan*/  sbq_base_dma; int /*<<< orphan*/  sbq_size; int /*<<< orphan*/ * cq_base; int /*<<< orphan*/  cq_base_dma; int /*<<< orphan*/  cq_size; } ;
struct ql_adapter {int /*<<< orphan*/  ndev; int /*<<< orphan*/  pdev; } ;
struct bq_desc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ifup ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_free_rx_resources (struct ql_adapter*,struct rx_ring*) ; 
 int /*<<< orphan*/  ql_init_lbq_ring (struct ql_adapter*,struct rx_ring*) ; 
 int /*<<< orphan*/  ql_init_sbq_ring (struct ql_adapter*,struct rx_ring*) ; 

__attribute__((used)) static int ql_alloc_rx_resources(struct ql_adapter *qdev,
				 struct rx_ring *rx_ring)
{

	/*
	 * Allocate the completion queue for this rx_ring.
	 */
	rx_ring->cq_base =
	    pci_alloc_consistent(qdev->pdev, rx_ring->cq_size,
				 &rx_ring->cq_base_dma);

	if (rx_ring->cq_base == NULL) {
		netif_err(qdev, ifup, qdev->ndev, "rx_ring alloc failed.\n");
		return -ENOMEM;
	}

	if (rx_ring->sbq_len) {
		/*
		 * Allocate small buffer queue.
		 */
		rx_ring->sbq_base =
		    pci_alloc_consistent(qdev->pdev, rx_ring->sbq_size,
					 &rx_ring->sbq_base_dma);

		if (rx_ring->sbq_base == NULL) {
			netif_err(qdev, ifup, qdev->ndev,
				  "Small buffer queue allocation failed.\n");
			goto err_mem;
		}

		/*
		 * Allocate small buffer queue control blocks.
		 */
		rx_ring->sbq =
		    kmalloc(rx_ring->sbq_len * sizeof(struct bq_desc),
			    GFP_KERNEL);
		if (rx_ring->sbq == NULL) {
			netif_err(qdev, ifup, qdev->ndev,
				  "Small buffer queue control block allocation failed.\n");
			goto err_mem;
		}

		ql_init_sbq_ring(qdev, rx_ring);
	}

	if (rx_ring->lbq_len) {
		/*
		 * Allocate large buffer queue.
		 */
		rx_ring->lbq_base =
		    pci_alloc_consistent(qdev->pdev, rx_ring->lbq_size,
					 &rx_ring->lbq_base_dma);

		if (rx_ring->lbq_base == NULL) {
			netif_err(qdev, ifup, qdev->ndev,
				  "Large buffer queue allocation failed.\n");
			goto err_mem;
		}
		/*
		 * Allocate large buffer queue control blocks.
		 */
		rx_ring->lbq =
		    kmalloc(rx_ring->lbq_len * sizeof(struct bq_desc),
			    GFP_KERNEL);
		if (rx_ring->lbq == NULL) {
			netif_err(qdev, ifup, qdev->ndev,
				  "Large buffer queue control block allocation failed.\n");
			goto err_mem;
		}

		ql_init_lbq_ring(qdev, rx_ring);
	}

	return 0;

err_mem:
	ql_free_rx_resources(qdev, rx_ring);
	return -ENOMEM;
}