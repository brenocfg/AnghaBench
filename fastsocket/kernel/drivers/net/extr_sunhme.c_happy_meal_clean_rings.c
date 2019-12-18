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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct happy_meal_txd {int /*<<< orphan*/  tx_flags; int /*<<< orphan*/  tx_addr; } ;
struct happy_meal_rxd {int /*<<< orphan*/  rx_addr; } ;
struct happy_meal {int /*<<< orphan*/  dma_dev; TYPE_1__* happy_block; struct sk_buff** tx_skbs; struct sk_buff** rx_skbs; } ;
struct TYPE_4__ {int nr_frags; } ;
struct TYPE_3__ {struct happy_meal_txd* happy_meal_txd; struct happy_meal_rxd* happy_meal_rxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int RX_BUF_ALLOC_SIZE ; 
 int RX_RING_SIZE ; 
 int TXFLAG_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int hme_read_desc32 (struct happy_meal*,int /*<<< orphan*/ *) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void happy_meal_clean_rings(struct happy_meal *hp)
{
	int i;

	for (i = 0; i < RX_RING_SIZE; i++) {
		if (hp->rx_skbs[i] != NULL) {
			struct sk_buff *skb = hp->rx_skbs[i];
			struct happy_meal_rxd *rxd;
			u32 dma_addr;

			rxd = &hp->happy_block->happy_meal_rxd[i];
			dma_addr = hme_read_desc32(hp, &rxd->rx_addr);
			dma_unmap_single(hp->dma_dev, dma_addr,
					 RX_BUF_ALLOC_SIZE, DMA_FROM_DEVICE);
			dev_kfree_skb_any(skb);
			hp->rx_skbs[i] = NULL;
		}
	}

	for (i = 0; i < TX_RING_SIZE; i++) {
		if (hp->tx_skbs[i] != NULL) {
			struct sk_buff *skb = hp->tx_skbs[i];
			struct happy_meal_txd *txd;
			u32 dma_addr;
			int frag;

			hp->tx_skbs[i] = NULL;

			for (frag = 0; frag <= skb_shinfo(skb)->nr_frags; frag++) {
				txd = &hp->happy_block->happy_meal_txd[i];
				dma_addr = hme_read_desc32(hp, &txd->tx_addr);
				dma_unmap_single(hp->dma_dev, dma_addr,
						 (hme_read_desc32(hp, &txd->tx_flags)
						  & TXFLAG_SIZE),
						 DMA_TO_DEVICE);

				if (frag != skb_shinfo(skb)->nr_frags)
					i++;
			}

			dev_kfree_skb_any(skb);
		}
	}
}