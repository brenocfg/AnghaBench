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
union e1000_adv_rx_desc {TYPE_2__ wb; } ;
struct sk_buff {int dummy; } ;
struct page {int /*<<< orphan*/  _count; } ;
struct igb_rx_buffer {int page_offset; struct page* page; } ;
struct igb_ring {int /*<<< orphan*/  q_vector; } ;
struct TYPE_6__ {int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (unsigned int,int) ; 
 int /*<<< orphan*/  E1000_RXDADV_STAT_TSIP ; 
 int IGB_RX_BUFSZ ; 
 unsigned int IGB_RX_HDR_LEN ; 
 scalar_t__ IGB_TS_HDR_LEN ; 
 int PAGE_SIZE ; 
 scalar_t__ SKB_DATA_ALIGN (unsigned int) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  igb_ptp_rx_pktstamp (int /*<<< orphan*/ ,unsigned char*,struct sk_buff*) ; 
 scalar_t__ igb_test_staterr (union e1000_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ numa_node_id () ; 
 unsigned char* page_address (struct page*) ; 
 int page_count (struct page*) ; 
 scalar_t__ page_to_nid (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,struct page*,int,unsigned int,int) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool igb_add_rx_frag(struct igb_ring *rx_ring,
			    struct igb_rx_buffer *rx_buffer,
			    union e1000_adv_rx_desc *rx_desc,
			    struct sk_buff *skb)
{
	struct page *page = rx_buffer->page;
	unsigned int size = le16_to_cpu(rx_desc->wb.upper.length);

	if ((size <= IGB_RX_HDR_LEN) && !skb_is_nonlinear(skb)) {
		unsigned char *va = page_address(page) + rx_buffer->page_offset;

		if (igb_test_staterr(rx_desc, E1000_RXDADV_STAT_TSIP)) {
			igb_ptp_rx_pktstamp(rx_ring->q_vector, va, skb);
			va += IGB_TS_HDR_LEN;
			size -= IGB_TS_HDR_LEN;
		}

		memcpy(__skb_put(skb, size), va, ALIGN(size, sizeof(long)));

		/* we can reuse buffer as-is, just make sure it is local */
		if (likely(page_to_nid(page) == numa_node_id()))
			return true;

		/* this page cannot be reused so discard it */
		put_page(page);
		return false;
	}

	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page,
			rx_buffer->page_offset, size, IGB_RX_BUFSZ);

	/* avoid re-using remote pages */
	if (unlikely(page_to_nid(page) != numa_node_id()))
		return false;

#if (PAGE_SIZE < 8192)
	/* if we are only owner of page we can reuse it */
	if (unlikely(page_count(page) != 1))
		return false;

	/* flip page offset to other buffer */
	rx_buffer->page_offset ^= IGB_RX_BUFSZ;

	/*
	 * since we are the only owner of the page and we need to
	 * increment it, just set the value to 2 in order to avoid
	 * an unnecessary locked operation
	 */
	atomic_set(&page->_count, 2);
#else
	/* move offset up to the next cache line */
	rx_buffer->page_offset += SKB_DATA_ALIGN(size);

	if (rx_buffer->page_offset > (PAGE_SIZE - IGB_RX_BUFSZ))
		return false;

	/* bump ref count on page before it is given to the stack */
	get_page(page);
#endif

	return true;
}