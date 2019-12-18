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
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct rx_ring {size_t lbq_clean_idx; int lbq_free_cnt; size_t lbq_len; size_t lbq_prod_idx; int /*<<< orphan*/  lbq_prod_idx_db_reg; int /*<<< orphan*/  lbq_buf_size; struct bq_desc* lbq; } ;
struct ql_adapter {int /*<<< orphan*/  ndev; int /*<<< orphan*/  pdev; } ;
struct TYPE_3__ {scalar_t__ offset; scalar_t__ map; } ;
struct TYPE_4__ {TYPE_1__ pg_chunk; } ;
struct bq_desc {int /*<<< orphan*/ * addr; TYPE_2__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,size_t) ; 
 int /*<<< orphan*/  netif_printk (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_addr_set (struct bq_desc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_len_set (struct bq_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ql_get_next_chunk (struct ql_adapter*,struct rx_ring*,struct bq_desc*) ; 
 int /*<<< orphan*/  ql_write_db_reg (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_status ; 

__attribute__((used)) static void ql_update_lbq(struct ql_adapter *qdev, struct rx_ring *rx_ring)
{
	u32 clean_idx = rx_ring->lbq_clean_idx;
	u32 start_idx = clean_idx;
	struct bq_desc *lbq_desc;
	u64 map;
	int i;

	while (rx_ring->lbq_free_cnt > 32) {
		for (i = (rx_ring->lbq_clean_idx % 16); i < 16; i++) {
			netif_printk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "lbq: try cleaning clean_idx = %d.\n",
				     clean_idx);
			lbq_desc = &rx_ring->lbq[clean_idx];
			if (ql_get_next_chunk(qdev, rx_ring, lbq_desc)) {
				rx_ring->lbq_clean_idx = clean_idx;
				netif_err(qdev, ifup, qdev->ndev,
						"Could not get a page chunk, i=%d, clean_idx =%d .\n",
						i, clean_idx);
				return;
			}

			map = lbq_desc->p.pg_chunk.map +
				lbq_desc->p.pg_chunk.offset;
				pci_unmap_addr_set(lbq_desc, mapaddr, map);
			pci_unmap_len_set(lbq_desc, maplen,
					rx_ring->lbq_buf_size);
				*lbq_desc->addr = cpu_to_le64(map);

			pci_dma_sync_single_for_device(qdev->pdev, map,
						rx_ring->lbq_buf_size,
						PCI_DMA_FROMDEVICE);
			clean_idx++;
			if (clean_idx == rx_ring->lbq_len)
				clean_idx = 0;
		}

		rx_ring->lbq_clean_idx = clean_idx;
		rx_ring->lbq_prod_idx += 16;
		if (rx_ring->lbq_prod_idx == rx_ring->lbq_len)
			rx_ring->lbq_prod_idx = 0;
		rx_ring->lbq_free_cnt -= 16;
	}

	if (start_idx != clean_idx) {
		netif_printk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "lbq: updating prod idx = %d.\n",
			     rx_ring->lbq_prod_idx);
		ql_write_db_reg(rx_ring->lbq_prod_idx,
				rx_ring->lbq_prod_idx_db_reg);
	}
}