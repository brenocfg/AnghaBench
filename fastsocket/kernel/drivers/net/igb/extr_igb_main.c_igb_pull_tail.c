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
typedef  union e1000_adv_rx_desc {int dummy; } e1000_adv_rx_desc ;
struct skb_frag_struct {unsigned int page_offset; } ;
struct sk_buff {unsigned int data_len; unsigned int tail; int /*<<< orphan*/  len; } ;
struct igb_ring {int /*<<< orphan*/  q_vector; } ;
struct TYPE_2__ {struct skb_frag_struct* frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (unsigned int,int) ; 
 int /*<<< orphan*/  E1000_RXDADV_STAT_TSIP ; 
 int /*<<< orphan*/  IGB_RX_HDR_LEN ; 
 unsigned int IGB_TS_HDR_LEN ; 
 unsigned int igb_get_headlen (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_ptp_rx_pktstamp (int /*<<< orphan*/ ,unsigned char*,struct sk_buff*) ; 
 scalar_t__ igb_test_staterr (union e1000_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* skb_frag_address (struct skb_frag_struct*) ; 
 int /*<<< orphan*/  skb_frag_size_sub (struct skb_frag_struct*,unsigned int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void igb_pull_tail(struct igb_ring *rx_ring,
			  union e1000_adv_rx_desc *rx_desc,
			  struct sk_buff *skb)
{
	struct skb_frag_struct *frag = &skb_shinfo(skb)->frags[0];
	unsigned char *va;
	unsigned int pull_len;

	/* it is valid to use page_address instead of kmap since we are
	 * working with pages allocated out of the lomem pool per
	 * alloc_page(GFP_ATOMIC)
	 */
	va = skb_frag_address(frag);

	if (igb_test_staterr(rx_desc, E1000_RXDADV_STAT_TSIP)) {
		/* retrieve timestamp from buffer */
		igb_ptp_rx_pktstamp(rx_ring->q_vector, va, skb);

		/* update pointers to remove timestamp header */
		skb_frag_size_sub(frag, IGB_TS_HDR_LEN);
		frag->page_offset += IGB_TS_HDR_LEN;
		skb->data_len -= IGB_TS_HDR_LEN;
		skb->len -= IGB_TS_HDR_LEN;

		/* move va to start of packet data */
		va += IGB_TS_HDR_LEN;
	}

	/* we need the header to contain the greater of either ETH_HLEN or
	 * 60 bytes if the skb->len is less than 60 for skb_pad.
	 */
	pull_len = igb_get_headlen(va, IGB_RX_HDR_LEN);

	/* align pull length to size of long to optimize memcpy performance */
	skb_copy_to_linear_data(skb, va, ALIGN(pull_len, sizeof(long)));

	/* update all of the pointers */
	skb_frag_size_sub(frag, pull_len);
	frag->page_offset += pull_len;
	skb->data_len -= pull_len;
	skb->tail += pull_len;
}