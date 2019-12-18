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
typedef  int u64 ;
struct tx_ring_info {int pending; scalar_t__ wrap_bit; scalar_t__ cons; scalar_t__ prod; TYPE_1__* tx_buffs; } ;
struct rx_ring_info {scalar_t__ rbr_refill_pending; scalar_t__ rbr_pending; scalar_t__ rcr_index; scalar_t__ rbr_table_size; scalar_t__ rbr_index; int /*<<< orphan*/ * rbr; struct page** rxhash; } ;
struct page {int index; scalar_t__ mapping; } ;
struct niu {int num_rx_rings; int num_tx_rings; struct tx_ring_info* tx_rings; struct rx_ring_info* rx_rings; } ;
struct TYPE_2__ {scalar_t__ skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_RBR_RING_SIZE ; 
 int MAX_TX_RING_SIZE ; 
 int RBR_DESCR_ADDR_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int niu_rbr_add_page (struct niu*,struct rx_ring_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_tx_packet (struct niu*,struct tx_ring_info*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void niu_reset_buffers(struct niu *np)
{
	int i, j, k, err;

	if (np->rx_rings) {
		for (i = 0; i < np->num_rx_rings; i++) {
			struct rx_ring_info *rp = &np->rx_rings[i];

			for (j = 0, k = 0; j < MAX_RBR_RING_SIZE; j++) {
				struct page *page;

				page = rp->rxhash[j];
				while (page) {
					struct page *next =
						(struct page *) page->mapping;
					u64 base = page->index;
					base = base >> RBR_DESCR_ADDR_SHIFT;
					rp->rbr[k++] = cpu_to_le32(base);
					page = next;
				}
			}
			for (; k < MAX_RBR_RING_SIZE; k++) {
				err = niu_rbr_add_page(np, rp, GFP_ATOMIC, k);
				if (unlikely(err))
					break;
			}

			rp->rbr_index = rp->rbr_table_size - 1;
			rp->rcr_index = 0;
			rp->rbr_pending = 0;
			rp->rbr_refill_pending = 0;
		}
	}
	if (np->tx_rings) {
		for (i = 0; i < np->num_tx_rings; i++) {
			struct tx_ring_info *rp = &np->tx_rings[i];

			for (j = 0; j < MAX_TX_RING_SIZE; j++) {
				if (rp->tx_buffs[j].skb)
					(void) release_tx_packet(np, rp, j);
			}

			rp->pending = MAX_TX_RING_SIZE;
			rp->prod = 0;
			rp->cons = 0;
			rp->wrap_bit = 0;
		}
	}
}