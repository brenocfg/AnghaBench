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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct page {int dummy; } ;
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  ca; TYPE_1__* rx_ring; int /*<<< orphan*/  max_ib_mtu; } ;
struct TYPE_2__ {struct sk_buff* skb; int /*<<< orphan*/ * mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IPOIB_UD_BUF_SIZE (int /*<<< orphan*/ ) ; 
 int IPOIB_UD_HEAD_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ib_dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ipoib_ud_need_sg (int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *ipoib_alloc_rx_skb(struct net_device *dev, int id)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct sk_buff *skb;
	int buf_size;
	int tailroom;
	u64 *mapping;

	if (ipoib_ud_need_sg(priv->max_ib_mtu)) {
		buf_size = IPOIB_UD_HEAD_SIZE;
		tailroom = 128; /* reserve some tailroom for IP/TCP headers */
	} else {
		buf_size = IPOIB_UD_BUF_SIZE(priv->max_ib_mtu);
		tailroom = 0;
	}

	skb = dev_alloc_skb(buf_size + tailroom + 4);
	if (unlikely(!skb))
		return NULL;

	/*
	 * IB will leave a 40 byte gap for a GRH and IPoIB adds a 4 byte
	 * header.  So we need 4 more bytes to get to 48 and align the
	 * IP header to a multiple of 16.
	 */
	skb_reserve(skb, 4);

	mapping = priv->rx_ring[id].mapping;
	mapping[0] = ib_dma_map_single(priv->ca, skb->data, buf_size,
				       DMA_FROM_DEVICE);
	if (unlikely(ib_dma_mapping_error(priv->ca, mapping[0])))
		goto error;

	if (ipoib_ud_need_sg(priv->max_ib_mtu)) {
		struct page *page = alloc_page(GFP_ATOMIC);
		if (!page)
			goto partial_error;
		skb_fill_page_desc(skb, 0, page, 0, PAGE_SIZE);
		mapping[1] =
			ib_dma_map_page(priv->ca, page,
					0, PAGE_SIZE, DMA_FROM_DEVICE);
		if (unlikely(ib_dma_mapping_error(priv->ca, mapping[1])))
			goto partial_error;
	}

	priv->rx_ring[id].skb = skb;
	return skb;

partial_error:
	ib_dma_unmap_single(priv->ca, mapping[0], buf_size, DMA_FROM_DEVICE);
error:
	dev_kfree_skb_any(skb);
	return NULL;
}