#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  size_t u16 ;
struct sk_buff {unsigned int len; unsigned int tail; unsigned int data_len; int /*<<< orphan*/  truesize; } ;
struct bnx2_sw_pg {int /*<<< orphan*/ * page; } ;
struct bnx2_rx_ring_info {size_t rx_pg_cons; size_t rx_pg_prod; struct bnx2_sw_pg* rx_pg_ring; } ;
struct bnx2 {TYPE_1__* pdev; int /*<<< orphan*/  rx_buf_use_size; } ;
struct TYPE_5__ {unsigned int size; } ;
typedef  TYPE_2__ skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {TYPE_2__* frags; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t BNX2_NEXT_RX_BD (size_t) ; 
 int /*<<< orphan*/  BNX2_RX_OFFSET ; 
 size_t BNX2_RX_PG_RING_IDX (size_t) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PAGE_ALIGN (unsigned int) ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int bnx2_alloc_rx_page (struct bnx2*,struct bnx2_rx_ring_info*,size_t,int /*<<< orphan*/ ) ; 
 int bnx2_alloc_rx_skb (struct bnx2*,struct bnx2_rx_ring_info*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_reuse_rx_skb (struct bnx2*,struct bnx2_rx_ring_info*,struct sk_buff*,size_t,size_t) ; 
 int /*<<< orphan*/  bnx2_reuse_rx_skb_pages (struct bnx2*,struct bnx2_rx_ring_info*,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pci_unmap_addr (struct bnx2_sw_pg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
bnx2_rx_skb(struct bnx2 *bp, struct bnx2_rx_ring_info *rxr, struct sk_buff *skb,
	    unsigned int len, unsigned int hdr_len, dma_addr_t dma_addr,
	    u32 ring_idx)
{
	int err;
	u16 prod = ring_idx & 0xffff;

	err = bnx2_alloc_rx_skb(bp, rxr, prod, GFP_ATOMIC);
	if (unlikely(err)) {
		bnx2_reuse_rx_skb(bp, rxr, skb, (u16) (ring_idx >> 16), prod);
		if (hdr_len) {
			unsigned int raw_len = len + 4;
			int pages = PAGE_ALIGN(raw_len - hdr_len) >> PAGE_SHIFT;

			bnx2_reuse_rx_skb_pages(bp, rxr, NULL, pages);
		}
		return err;
	}

	skb_reserve(skb, BNX2_RX_OFFSET);
	dma_unmap_single(&bp->pdev->dev, dma_addr, bp->rx_buf_use_size,
			 PCI_DMA_FROMDEVICE);

	if (hdr_len == 0) {
		skb_put(skb, len);
		return 0;
	} else {
		unsigned int i, frag_len, frag_size, pages;
		struct bnx2_sw_pg *rx_pg;
		u16 pg_cons = rxr->rx_pg_cons;
		u16 pg_prod = rxr->rx_pg_prod;

		frag_size = len + 4 - hdr_len;
		pages = PAGE_ALIGN(frag_size) >> PAGE_SHIFT;
		skb_put(skb, hdr_len);

		for (i = 0; i < pages; i++) {
			dma_addr_t mapping_old;

			frag_len = min(frag_size, (unsigned int) PAGE_SIZE);
			if (unlikely(frag_len <= 4)) {
				unsigned int tail = 4 - frag_len;

				rxr->rx_pg_cons = pg_cons;
				rxr->rx_pg_prod = pg_prod;
				bnx2_reuse_rx_skb_pages(bp, rxr, NULL,
							pages - i);
				skb->len -= tail;
				if (i == 0) {
					skb->tail -= tail;
				} else {
					skb_frag_t *frag =
						&skb_shinfo(skb)->frags[i - 1];
					frag->size -= tail;
					skb->data_len -= tail;
				}
				return 0;
			}
			rx_pg = &rxr->rx_pg_ring[pg_cons];

			/* Don't unmap yet.  If we're unable to allocate a new
			 * page, we need to recycle the page and the DMA addr.
			 */
			mapping_old = pci_unmap_addr(rx_pg, mapping);
			if (i == pages - 1)
				frag_len -= 4;

			skb_fill_page_desc(skb, i, rx_pg->page, 0, frag_len);
			rx_pg->page = NULL;

			err = bnx2_alloc_rx_page(bp, rxr,
						 BNX2_RX_PG_RING_IDX(pg_prod),
						 GFP_ATOMIC);
			if (unlikely(err)) {
				rxr->rx_pg_cons = pg_cons;
				rxr->rx_pg_prod = pg_prod;
				bnx2_reuse_rx_skb_pages(bp, rxr, skb,
							pages - i);
				return err;
			}

			dma_unmap_page(&bp->pdev->dev, mapping_old,
				       PAGE_SIZE, PCI_DMA_FROMDEVICE);

			frag_size -= frag_len;
			skb->data_len += frag_len;
			skb->truesize += PAGE_SIZE;
			skb->len += frag_len;

			pg_prod = BNX2_NEXT_RX_BD(pg_prod);
			pg_cons = BNX2_RX_PG_RING_IDX(BNX2_NEXT_RX_BD(pg_cons));
		}
		rxr->rx_pg_prod = pg_prod;
		rxr->rx_pg_cons = pg_cons;
	}
	return 0;
}