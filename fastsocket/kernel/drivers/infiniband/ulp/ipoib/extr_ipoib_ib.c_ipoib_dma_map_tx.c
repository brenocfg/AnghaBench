#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct ipoib_tx_buf {int /*<<< orphan*/ * mapping; struct sk_buff* skb; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  page_offset; } ;
typedef  TYPE_1__ skb_frag_t ;
struct TYPE_5__ {int nr_frags; TYPE_1__* frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  ib_dma_map_page (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_map_single (struct ib_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_mapping_error (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_page (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (struct ib_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_page (TYPE_1__*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipoib_dma_map_tx(struct ib_device *ca,
			    struct ipoib_tx_buf *tx_req)
{
	struct sk_buff *skb = tx_req->skb;
	u64 *mapping = tx_req->mapping;
	int i;
	int off;

	if (skb_headlen(skb)) {
		mapping[0] = ib_dma_map_single(ca, skb->data, skb_headlen(skb),
					       DMA_TO_DEVICE);
		if (unlikely(ib_dma_mapping_error(ca, mapping[0])))
			return -EIO;

		off = 1;
	} else
		off = 0;

	for (i = 0; i < skb_shinfo(skb)->nr_frags; ++i) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		mapping[i + off] = ib_dma_map_page(ca,
						 skb_frag_page(frag),
						 frag->page_offset, frag->size,
						 DMA_TO_DEVICE);
		if (unlikely(ib_dma_mapping_error(ca, mapping[i + off])))
			goto partial_error;
	}
	return 0;

partial_error:
	for (; i > 0; --i) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i - 1];
		ib_dma_unmap_page(ca, mapping[i - !off], frag->size, DMA_TO_DEVICE);
	}

	if (off)
		ib_dma_unmap_single(ca, mapping[0], skb_headlen(skb), DMA_TO_DEVICE);

	return -EIO;
}