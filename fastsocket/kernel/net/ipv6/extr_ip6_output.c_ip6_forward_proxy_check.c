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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ data; } ;
struct ipv6hdr {scalar_t__ nexthdr; int /*<<< orphan*/  daddr; } ;
struct icmp6hdr {int icmp6_type; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_ICMPV6 ; 
 int IPV6_ADDR_LINKLOCAL ; 
#define  NDISC_NEIGHBOUR_ADVERTISEMENT 132 
#define  NDISC_NEIGHBOUR_SOLICITATION 131 
#define  NDISC_REDIRECT 130 
#define  NDISC_ROUTER_ADVERTISEMENT 129 
#define  NDISC_ROUTER_SOLICITATION 128 
 int /*<<< orphan*/  dst_link_failure (struct sk_buff*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 scalar_t__ ipv6_ext_hdr (scalar_t__) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int ipv6_skip_exthdr (struct sk_buff*,int,scalar_t__*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static int ip6_forward_proxy_check(struct sk_buff *skb)
{
	struct ipv6hdr *hdr = ipv6_hdr(skb);
	u8 nexthdr = hdr->nexthdr;
	int offset;

	if (ipv6_ext_hdr(nexthdr)) {
		offset = ipv6_skip_exthdr(skb, sizeof(*hdr), &nexthdr);
		if (offset < 0)
			return 0;
	} else
		offset = sizeof(struct ipv6hdr);

	if (nexthdr == IPPROTO_ICMPV6) {
		struct icmp6hdr *icmp6;

		if (!pskb_may_pull(skb, (skb_network_header(skb) +
					 offset + 1 - skb->data)))
			return 0;

		icmp6 = (struct icmp6hdr *)(skb_network_header(skb) + offset);

		switch (icmp6->icmp6_type) {
		case NDISC_ROUTER_SOLICITATION:
		case NDISC_ROUTER_ADVERTISEMENT:
		case NDISC_NEIGHBOUR_SOLICITATION:
		case NDISC_NEIGHBOUR_ADVERTISEMENT:
		case NDISC_REDIRECT:
			/* For reaction involving unicast neighbor discovery
			 * message destined to the proxied address, pass it to
			 * input function.
			 */
			return 1;
		default:
			break;
		}
	}

	/*
	 * The proxying router can't forward traffic sent to a link-local
	 * address, so signal the sender and discard the packet. This
	 * behavior is clarified by the MIPv6 specification.
	 */
	if (ipv6_addr_type(&hdr->daddr) & IPV6_ADDR_LINKLOCAL) {
		dst_link_failure(skb);
		return -1;
	}

	return 0;
}