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
struct sk_buff {unsigned int len; unsigned int tail; scalar_t__ data_len; int /*<<< orphan*/  data; int /*<<< orphan*/  dev; } ;
struct mlx4_en_rx_desc {TYPE_1__* data; } ;
struct mlx4_en_rx_alloc {int offset; int /*<<< orphan*/  page; } ;
struct mlx4_en_priv {int /*<<< orphan*/  ddev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int nr_frags; TYPE_2__* frags; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  page_offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ HEADER_COPY_SIZE ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  RX_ERR ; 
 unsigned int SMALL_PACKET_SIZE ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int mlx4_en_complete_rx_desc (struct mlx4_en_priv*,struct mlx4_en_rx_desc*,struct mlx4_en_rx_alloc*,struct sk_buff*,unsigned int) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,void*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *mlx4_en_rx_skb(struct mlx4_en_priv *priv,
				      struct mlx4_en_rx_desc *rx_desc,
				      struct mlx4_en_rx_alloc *frags,
				      unsigned int length)
{
	struct sk_buff *skb;
	void *va;
	int used_frags;
	dma_addr_t dma;

	skb = dev_alloc_skb(SMALL_PACKET_SIZE + NET_IP_ALIGN);
	if (!skb) {
		en_dbg(RX_ERR, priv, "Failed allocating skb\n");
		return NULL;
	}
	skb->dev = priv->dev;
	skb_reserve(skb, NET_IP_ALIGN);
	skb->len = length;

	/* Get pointer to first fragment so we could copy the headers into the
	 * (linear part of the) skb */
	va = page_address(frags[0].page) + frags[0].offset;

	if (length <= SMALL_PACKET_SIZE) {
		/* We are copying all relevant data to the skb - temporarily
		 * sync buffers for the copy */
		dma = be64_to_cpu(rx_desc->data[0].addr);
		dma_sync_single_for_cpu(priv->ddev, dma, length,
					DMA_FROM_DEVICE);
		skb_copy_to_linear_data(skb, va, length);
		skb->tail += length;
	} else {
		/* Move relevant fragments to skb */
		used_frags = mlx4_en_complete_rx_desc(priv, rx_desc, frags,
							skb, length);
		if (unlikely(!used_frags)) {
			kfree_skb(skb);
			return NULL;
		}
		skb_shinfo(skb)->nr_frags = used_frags;

		/* Copy headers into the skb linear buffer */
		memcpy(skb->data, va, HEADER_COPY_SIZE);
		skb->tail += HEADER_COPY_SIZE;

		/* Skip headers in first fragment */
		skb_shinfo(skb)->frags[0].page_offset += HEADER_COPY_SIZE;

		/* Adjust size of first fragment */
		skb_shinfo(skb)->frags[0].size -= HEADER_COPY_SIZE;
		skb->data_len = length - HEADER_COPY_SIZE;
	}
	return skb;
}