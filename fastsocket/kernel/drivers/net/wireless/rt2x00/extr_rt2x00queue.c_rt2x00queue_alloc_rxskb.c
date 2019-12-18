#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct skb_frame_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  skb_dma; struct queue_entry* entry; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rt2x00_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  cap_flags; } ;
struct queue_entry {struct data_queue* queue; } ;
struct data_queue {unsigned int data_size; unsigned int desc_size; unsigned int winfo_size; struct rt2x00_dev* rt2x00dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_HW_CRYPTO ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  REQUIRE_DMA ; 
 int /*<<< orphan*/  SKBDESC_DMA_MAPPED_RX ; 
 struct sk_buff* __dev_alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct skb_frame_desc* get_skb_frame_desc (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct skb_frame_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct sk_buff *rt2x00queue_alloc_rxskb(struct queue_entry *entry, gfp_t gfp)
{
	struct data_queue *queue = entry->queue;
	struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	struct sk_buff *skb;
	struct skb_frame_desc *skbdesc;
	unsigned int frame_size;
	unsigned int head_size = 0;
	unsigned int tail_size = 0;

	/*
	 * The frame size includes descriptor size, because the
	 * hardware directly receive the frame into the skbuffer.
	 */
	frame_size = queue->data_size + queue->desc_size + queue->winfo_size;

	/*
	 * The payload should be aligned to a 4-byte boundary,
	 * this means we need at least 3 bytes for moving the frame
	 * into the correct offset.
	 */
	head_size = 4;

	/*
	 * For IV/EIV/ICV assembly we must make sure there is
	 * at least 8 bytes bytes available in headroom for IV/EIV
	 * and 8 bytes for ICV data as tailroon.
	 */
	if (test_bit(CAPABILITY_HW_CRYPTO, &rt2x00dev->cap_flags)) {
		head_size += 8;
		tail_size += 8;
	}

	/*
	 * Allocate skbuffer.
	 */
	skb = __dev_alloc_skb(frame_size + head_size + tail_size, gfp);
	if (!skb)
		return NULL;

	/*
	 * Make sure we not have a frame with the requested bytes
	 * available in the head and tail.
	 */
	skb_reserve(skb, head_size);
	skb_put(skb, frame_size);

	/*
	 * Populate skbdesc.
	 */
	skbdesc = get_skb_frame_desc(skb);
	memset(skbdesc, 0, sizeof(*skbdesc));
	skbdesc->entry = entry;

	if (test_bit(REQUIRE_DMA, &rt2x00dev->cap_flags)) {
		dma_addr_t skb_dma;

		skb_dma = dma_map_single(rt2x00dev->dev, skb->data, skb->len,
					 DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(rt2x00dev->dev, skb_dma))) {
			dev_kfree_skb_any(skb);
			return NULL;
		}

		skbdesc->skb_dma = skb_dma;
		skbdesc->flags |= SKBDESC_DMA_MAPPED_RX;
	}

	return skb;
}