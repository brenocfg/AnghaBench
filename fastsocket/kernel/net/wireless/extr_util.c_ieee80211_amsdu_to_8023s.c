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
typedef  unsigned int u8 ;
typedef  unsigned int u16 ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {unsigned int* data; int len; int /*<<< orphan*/  priority; int /*<<< orphan*/  dev; } ;
struct ethhdr {unsigned int h_proto; unsigned int* h_dest; unsigned int* h_source; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
typedef  unsigned int __be16 ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int const,int) ; 
 int ETH_ALEN ; 
 unsigned int ETH_P_AARP ; 
 unsigned int ETH_P_IPX ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  bridge_tunnel_header ; 
 struct sk_buff* dev_alloc_skb (unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ ether_addr_equal (unsigned int*,int /*<<< orphan*/ ) ; 
 int ieee80211_data_to_8023 (struct sk_buff*,unsigned int const*,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,int) ; 
 unsigned int ntohs (unsigned int) ; 
 int /*<<< orphan*/  rfc1042_header ; 
 scalar_t__ skb_pull (struct sk_buff*,int) ; 
 unsigned int* skb_push (struct sk_buff*,int) ; 
 unsigned int* skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

void ieee80211_amsdu_to_8023s(struct sk_buff *skb, struct sk_buff_head *list,
			      const u8 *addr, enum nl80211_iftype iftype,
			      const unsigned int extra_headroom,
			      bool has_80211_header)
{
	struct sk_buff *frame = NULL;
	u16 ethertype;
	u8 *payload;
	const struct ethhdr *eth;
	int remaining, err;
	u8 dst[ETH_ALEN], src[ETH_ALEN];

	if (has_80211_header) {
		err = ieee80211_data_to_8023(skb, addr, iftype);
		if (err)
			goto out;

		/* skip the wrapping header */
		eth = (struct ethhdr *) skb_pull(skb, sizeof(struct ethhdr));
		if (!eth)
			goto out;
	} else {
		eth = (struct ethhdr *) skb->data;
	}

	while (skb != frame) {
		u8 padding;
		__be16 len = eth->h_proto;
		unsigned int subframe_len = sizeof(struct ethhdr) + ntohs(len);

		remaining = skb->len;
		memcpy(dst, eth->h_dest, ETH_ALEN);
		memcpy(src, eth->h_source, ETH_ALEN);

		padding = (4 - subframe_len) & 0x3;
		/* the last MSDU has no padding */
		if (subframe_len > remaining)
			goto purge;

		skb_pull(skb, sizeof(struct ethhdr));
		/* reuse skb for the last subframe */
		if (remaining <= subframe_len + padding)
			frame = skb;
		else {
			unsigned int hlen = ALIGN(extra_headroom, 4);
			/*
			 * Allocate and reserve two bytes more for payload
			 * alignment since sizeof(struct ethhdr) is 14.
			 */
			frame = dev_alloc_skb(hlen + subframe_len + 2);
			if (!frame)
				goto purge;

			skb_reserve(frame, hlen + sizeof(struct ethhdr) + 2);
			memcpy(skb_put(frame, ntohs(len)), skb->data,
				ntohs(len));

			eth = (struct ethhdr *)skb_pull(skb, ntohs(len) +
							padding);
			if (!eth) {
				dev_kfree_skb(frame);
				goto purge;
			}
		}

		skb_reset_network_header(frame);
		frame->dev = skb->dev;
		frame->priority = skb->priority;

		payload = frame->data;
		ethertype = (payload[6] << 8) | payload[7];

		if (likely((ether_addr_equal(payload, rfc1042_header) &&
			    ethertype != ETH_P_AARP && ethertype != ETH_P_IPX) ||
			   ether_addr_equal(payload, bridge_tunnel_header))) {
			/* remove RFC1042 or Bridge-Tunnel
			 * encapsulation and replace EtherType */
			skb_pull(frame, 6);
			memcpy(skb_push(frame, ETH_ALEN), src, ETH_ALEN);
			memcpy(skb_push(frame, ETH_ALEN), dst, ETH_ALEN);
		} else {
			memcpy(skb_push(frame, sizeof(__be16)), &len,
				sizeof(__be16));
			memcpy(skb_push(frame, ETH_ALEN), src, ETH_ALEN);
			memcpy(skb_push(frame, ETH_ALEN), dst, ETH_ALEN);
		}
		__skb_queue_tail(list, frame);
	}

	return;

 purge:
	__skb_queue_purge(list);
 out:
	dev_kfree_skb(skb);
}