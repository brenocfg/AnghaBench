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
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
struct TYPE_5__ {TYPE_1__ upper; } ;
union ixgbe_adv_rx_desc {TYPE_2__ wb; } ;
struct sk_buff {int dummy; } ;
struct page {int /*<<< orphan*/  _count; } ;
struct ixgbe_rx_buffer {int page_offset; struct page* page; } ;
struct ixgbe_ring {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 unsigned int IXGBE_RX_HDR_SIZE ; 
 int L1_CACHE_BYTES ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 unsigned int ixgbe_rx_bufsz (struct ixgbe_ring*) ; 
 unsigned int ixgbe_rx_pg_size (struct ixgbe_ring*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 scalar_t__ numa_node_id () ; 
 unsigned char* page_address (struct page*) ; 
 int page_count (struct page*) ; 
 scalar_t__ page_to_nid (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,struct page*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ixgbe_add_rx_frag(struct ixgbe_ring *rx_ring,
			      struct ixgbe_rx_buffer *rx_buffer,
			      union ixgbe_adv_rx_desc *rx_desc,
			      struct sk_buff *skb)
{
	struct page *page = rx_buffer->page;
	unsigned int size = le16_to_cpu(rx_desc->wb.upper.length);
#if (PAGE_SIZE < 8192)
	unsigned int truesize = ixgbe_rx_bufsz(rx_ring);
#else
	unsigned int truesize = ALIGN(size, L1_CACHE_BYTES);
	unsigned int last_offset = ixgbe_rx_pg_size(rx_ring) -
				   ixgbe_rx_bufsz(rx_ring);
#endif

	if ((size <= IXGBE_RX_HDR_SIZE) && !skb_is_nonlinear(skb)) {
		unsigned char *va = page_address(page) + rx_buffer->page_offset;

		memcpy(__skb_put(skb, size), va, ALIGN(size, sizeof(long)));

		/* we can reuse buffer as-is, just make sure it is local */
		if (likely(page_to_nid(page) == numa_node_id()))
			return true;

		/* this page cannot be reused so discard it */
		put_page(page);
		return false;
	}

	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page,
			rx_buffer->page_offset, size, truesize);

	/* avoid re-using remote pages */
	if (unlikely(page_to_nid(page) != numa_node_id()))
		return false;

#if (PAGE_SIZE < 8192)
	/* if we are only owner of page we can reuse it */
	if (unlikely(page_count(page) != 1))
		return false;

	/* flip page offset to other buffer */
	rx_buffer->page_offset ^= truesize;

	/*
	 * since we are the only owner of the page and we need to
	 * increment it, just set the value to 2 in order to avoid
	 * an unecessary locked operation
	 */
	atomic_set(&page->_count, 2);
#else
	/* move offset up to the next cache line */
	rx_buffer->page_offset += truesize;

	if (rx_buffer->page_offset > last_offset)
		return false;

	/* bump ref count on page before it is given to the stack */
	get_page(page);
#endif

	return true;
}