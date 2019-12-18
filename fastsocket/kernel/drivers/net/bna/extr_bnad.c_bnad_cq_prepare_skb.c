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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  truesize; int /*<<< orphan*/  data_len; int /*<<< orphan*/  len; } ;
struct bnad_rx_unmap_q {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {scalar_t__ len; } ;
struct bnad_rx_unmap {TYPE_3__ vector; struct sk_buff* skb; int /*<<< orphan*/ * page; int /*<<< orphan*/  page_offset; } ;
struct bnad_rx_ctrl {int /*<<< orphan*/  napi; struct bnad* bnad; } ;
struct bnad {int /*<<< orphan*/  netdev; TYPE_1__* pcidev; } ;
struct TYPE_5__ {int /*<<< orphan*/  nr_frags; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BNAD_RXBUF_IS_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_unmap_addr (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* napi_get_frags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct sk_buff *
bnad_cq_prepare_skb(struct bnad_rx_ctrl *rx_ctrl,
		struct bnad_rx_unmap_q *unmap_q,
		struct bnad_rx_unmap *unmap,
		u32 length, u32 flags)
{
	struct bnad *bnad = rx_ctrl->bnad;
	struct sk_buff *skb;

	if (BNAD_RXBUF_IS_PAGE(unmap_q->type)) {
		skb = napi_get_frags(&rx_ctrl->napi);
		if (unlikely(!skb))
			return NULL;

		dma_unmap_page(&bnad->pcidev->dev,
				dma_unmap_addr(&unmap->vector, dma_addr),
				unmap->vector.len, DMA_FROM_DEVICE);
		skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags,
				unmap->page, unmap->page_offset, length);
		skb->len += length;
		skb->data_len += length;
		skb->truesize += length;

		unmap->page = NULL;
		unmap->vector.len = 0;

		return skb;
	}

	skb = unmap->skb;
	BUG_ON(!skb);

	dma_unmap_single(&bnad->pcidev->dev,
			dma_unmap_addr(&unmap->vector, dma_addr),
			unmap->vector.len, DMA_FROM_DEVICE);

	skb_put(skb, length);

	skb->protocol = eth_type_trans(skb, bnad->netdev);

	unmap->skb = NULL;
	unmap->vector.len = 0;
	return skb;
}