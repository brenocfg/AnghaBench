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
struct sk_buff {int transport_header; } ;
struct ipv6hdr {int dummy; } ;
struct inet6_skb_parm {int hop; int nhoff; } ;

/* Variables and functions */
 struct inet6_skb_parm* IP6CB (struct sk_buff*) ; 
 scalar_t__ ip6_parse_tlv (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int* skb_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  tlvprochopopt_lst ; 

int ipv6_parse_hopopts(struct sk_buff *skb)
{
	struct inet6_skb_parm *opt = IP6CB(skb);

	/*
	 * skb_network_header(skb) is equal to skb->data, and
	 * skb_network_header_len(skb) is always equal to
	 * sizeof(struct ipv6hdr) by definition of
	 * hop-by-hop options.
	 */
	if (!pskb_may_pull(skb, sizeof(struct ipv6hdr) + 8) ||
	    !pskb_may_pull(skb, (sizeof(struct ipv6hdr) +
				 ((skb_transport_header(skb)[1] + 1) << 3)))) {
		kfree_skb(skb);
		return -1;
	}

	opt->hop = sizeof(struct ipv6hdr);
	if (ip6_parse_tlv(tlvprochopopt_lst, skb)) {
		skb->transport_header += (skb_transport_header(skb)[1] + 1) << 3;
		opt = IP6CB(skb);
		opt->nhoff = sizeof(struct ipv6hdr);
		return 1;
	}
	return -1;
}