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
typedef  size_t uint32_t ;
struct rx_ring {size_t lbq_curr_idx; size_t lbq_clean_idx; size_t lbq_len; struct bq_desc* lbq; } ;
struct ql_adapter {int /*<<< orphan*/  pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * page; scalar_t__ last_flag; int /*<<< orphan*/  map; } ;
struct TYPE_4__ {TYPE_1__ pg_chunk; } ;
struct bq_desc {TYPE_2__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_lbq_block_size (struct ql_adapter*) ; 

__attribute__((used)) static void ql_free_lbq_buffers(struct ql_adapter *qdev, struct rx_ring *rx_ring)
{
	struct bq_desc *lbq_desc;

	uint32_t  curr_idx, clean_idx;

	curr_idx = rx_ring->lbq_curr_idx;
	clean_idx = rx_ring->lbq_clean_idx;
	while (curr_idx != clean_idx) {
		lbq_desc = &rx_ring->lbq[curr_idx];

		if (lbq_desc->p.pg_chunk.last_flag) {
			pci_unmap_page(qdev->pdev,
				lbq_desc->p.pg_chunk.map,
				ql_lbq_block_size(qdev),
				       PCI_DMA_FROMDEVICE);
			lbq_desc->p.pg_chunk.last_flag = 0;
		}

		put_page(lbq_desc->p.pg_chunk.page);
		lbq_desc->p.pg_chunk.page = NULL;

		if (++curr_idx == rx_ring->lbq_len)
			curr_idx = 0;

	}
}