#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct meth_private {scalar_t__ rx_write; int /*<<< orphan*/ * rx_ring_dmas; int /*<<< orphan*/ ** rx_ring; TYPE_2__** rx_skbs; } ;
typedef  int /*<<< orphan*/  rx_packet ;
struct TYPE_5__ {int /*<<< orphan*/  rx_fifo; } ;
struct TYPE_7__ {TYPE_1__ eth; } ;
struct TYPE_6__ {scalar_t__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  METH_RX_BUFF_SIZE ; 
 int /*<<< orphan*/  METH_RX_HEAD ; 
 int RX_RING_ENTRIES ; 
 TYPE_2__* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* mace ; 
 int /*<<< orphan*/  skb_reserve (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meth_init_rx_ring(struct meth_private *priv)
{
	int i;

	for (i = 0; i < RX_RING_ENTRIES; i++) {
		priv->rx_skbs[i] = alloc_skb(METH_RX_BUFF_SIZE, 0);
		/* 8byte status vector + 3quad padding + 2byte padding,
		 * to put data on 64bit aligned boundary */
		skb_reserve(priv->rx_skbs[i],METH_RX_HEAD);
		priv->rx_ring[i]=(rx_packet*)(priv->rx_skbs[i]->head);
		/* I'll need to re-sync it after each RX */
		priv->rx_ring_dmas[i] =
			dma_map_single(NULL, priv->rx_ring[i],
				       METH_RX_BUFF_SIZE, DMA_FROM_DEVICE);
		mace->eth.rx_fifo = priv->rx_ring_dmas[i];
	}
        priv->rx_write = 0;
	return 0;
}