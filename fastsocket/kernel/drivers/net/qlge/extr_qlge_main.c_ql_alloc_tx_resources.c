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
struct tx_ring_desc {int dummy; } ;
struct tx_ring {int wq_base_dma; int wq_len; int /*<<< orphan*/ * wq_base; int /*<<< orphan*/  wq_size; int /*<<< orphan*/ * q; } ;
struct ql_adapter {int /*<<< orphan*/  ndev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WQ_ADDR_ALIGN ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ql_alloc_tx_resources(struct ql_adapter *qdev,
				 struct tx_ring *tx_ring)
{
	tx_ring->wq_base =
	    pci_alloc_consistent(qdev->pdev, tx_ring->wq_size,
				 &tx_ring->wq_base_dma);

	if ((tx_ring->wq_base == NULL) ||
	    tx_ring->wq_base_dma & WQ_ADDR_ALIGN)
		goto pci_alloc_err;

	tx_ring->q =
	    kmalloc(tx_ring->wq_len * sizeof(struct tx_ring_desc), GFP_KERNEL);
	if (tx_ring->q == NULL)
		goto err;

	return 0;
err:
	pci_free_consistent(qdev->pdev, tx_ring->wq_size,
			    tx_ring->wq_base, tx_ring->wq_base_dma);
	tx_ring->wq_base = NULL;
pci_alloc_err:
	netif_err(qdev, ifup, qdev->ndev, "tx_ring alloc failed.\n");
	return -ENOMEM;
}