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
typedef  size_t u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct bnad_rx_unmap_q {struct bnad_rx_unmap* unmap; } ;
struct TYPE_6__ {size_t len; } ;
struct bnad_rx_unmap {TYPE_3__ vector; struct sk_buff* skb; } ;
struct bnad {TYPE_2__* pcidev; int /*<<< orphan*/  netdev; } ;
struct bna_rxq_entry {int /*<<< orphan*/  host_addr; } ;
struct bna_rcb {size_t producer_index; size_t q_depth; int /*<<< orphan*/  flags; scalar_t__ sw_q; TYPE_1__* rxq; struct bnad_rx_unmap_q* unmap_q; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {size_t buffer_size; int /*<<< orphan*/  rxbuf_alloc_failed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RXQ_POST_OK ; 
 int /*<<< orphan*/  BNAD_UPDATE_CTR (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNA_QE_INDX_INC (size_t,size_t) ; 
 int /*<<< orphan*/  BNA_SET_DMA_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  bna_rxq_prod_indx_doorbell (struct bna_rcb*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (size_t) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  rxbuf_alloc_failed ; 
 int /*<<< orphan*/  smp_mb () ; 
 size_t test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32
bnad_rxq_refill_skb(struct bnad *bnad, struct bna_rcb *rcb, u32 nalloc)
{
	u32 alloced, prod, q_depth, buff_sz;
	struct bnad_rx_unmap_q *unmap_q = rcb->unmap_q;
	struct bnad_rx_unmap *unmap;
	struct bna_rxq_entry *rxent;
	struct sk_buff *skb;
	dma_addr_t dma_addr;

	buff_sz = rcb->rxq->buffer_size;
	prod = rcb->producer_index;
	q_depth = rcb->q_depth;

	alloced = 0;
	while (nalloc--) {
		unmap = &unmap_q->unmap[prod];

		skb = netdev_alloc_skb_ip_align(bnad->netdev, buff_sz);

		if (unlikely(!skb)) {
			BNAD_UPDATE_CTR(bnad, rxbuf_alloc_failed);
			rcb->rxq->rxbuf_alloc_failed++;
			goto finishing;
		}
		dma_addr = dma_map_single(&bnad->pcidev->dev, skb->data,
					  buff_sz, DMA_FROM_DEVICE);

		unmap->skb = skb;
		dma_unmap_addr_set(&unmap->vector, dma_addr, dma_addr);
		unmap->vector.len = buff_sz;

		rxent = &((struct bna_rxq_entry *)rcb->sw_q)[prod];
		BNA_SET_DMA_ADDR(dma_addr, &rxent->host_addr);
		BNA_QE_INDX_INC(prod, q_depth);
		alloced++;
	}

finishing:
	if (likely(alloced)) {
		rcb->producer_index = prod;
		smp_mb();
		if (likely(test_bit(BNAD_RXQ_POST_OK, &rcb->flags)))
			bna_rxq_prod_indx_doorbell(rcb);
	}

	return alloced;
}