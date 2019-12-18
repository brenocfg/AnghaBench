#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {scalar_t__ offset; int last_flag; int /*<<< orphan*/ * page; int /*<<< orphan*/  va; int /*<<< orphan*/  map; } ;
struct rx_ring {scalar_t__ lbq_buf_size; TYPE_1__ pg_chunk; } ;
struct ql_adapter {int /*<<< orphan*/  ndev; int /*<<< orphan*/  lbq_buf_order; int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {TYPE_1__ pg_chunk; } ;
struct bq_desc {TYPE_2__ p; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int __GFP_COLD ; 
 int __GFP_COMP ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alloc_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ql_lbq_block_size (struct ql_adapter*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ql_get_next_chunk(struct ql_adapter *qdev, struct rx_ring *rx_ring,
						struct bq_desc *lbq_desc)
{
	if (!rx_ring->pg_chunk.page) {
		u64 map;
		rx_ring->pg_chunk.page = alloc_pages(__GFP_COLD | __GFP_COMP |
						GFP_ATOMIC,
						qdev->lbq_buf_order);
		if (unlikely(!rx_ring->pg_chunk.page)) {
			netif_err(qdev, drv, qdev->ndev,
				  "page allocation failed.\n");
			return -ENOMEM;
		}
		rx_ring->pg_chunk.offset = 0;
		map = pci_map_page(qdev->pdev, rx_ring->pg_chunk.page,
					0, ql_lbq_block_size(qdev),
					PCI_DMA_FROMDEVICE);
		if (pci_dma_mapping_error(qdev->pdev, map)) {
			__free_pages(rx_ring->pg_chunk.page,
					qdev->lbq_buf_order);
			netif_err(qdev, drv, qdev->ndev,
				  "PCI mapping failed.\n");
			return -ENOMEM;
		}
		rx_ring->pg_chunk.map = map;
		rx_ring->pg_chunk.va = page_address(rx_ring->pg_chunk.page);
	}

	/* Copy the current master pg_chunk info
	 * to the current descriptor.
	 */
	lbq_desc->p.pg_chunk = rx_ring->pg_chunk;

	/* Adjust the master page chunk for next
	 * buffer get.
	 */
	rx_ring->pg_chunk.offset += rx_ring->lbq_buf_size;
	if (rx_ring->pg_chunk.offset == ql_lbq_block_size(qdev)) {
		rx_ring->pg_chunk.page = NULL;
		lbq_desc->p.pg_chunk.last_flag = 1;
	} else {
		rx_ring->pg_chunk.va += rx_ring->lbq_buf_size;
		get_page(rx_ring->pg_chunk.page);
		lbq_desc->p.pg_chunk.last_flag = 0;
	}
	return 0;
}