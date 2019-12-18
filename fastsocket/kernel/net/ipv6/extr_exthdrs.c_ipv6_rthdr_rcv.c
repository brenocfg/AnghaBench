#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct sk_buff {scalar_t__ pkt_type; int transport_header; scalar_t__ ip_summed; int data; TYPE_7__* dev; } ;
struct rt0_hdr {struct in6_addr* addr; } ;
struct TYPE_11__ {TYPE_1__* devconf_all; } ;
struct net {TYPE_2__ ipv6; } ;
struct ipv6_rt_hdr {int segments_left; int type; int hdrlen; int /*<<< orphan*/  nexthdr; } ;
struct inet6_skb_parm {int /*<<< orphan*/ * nhoff; scalar_t__ dst1; scalar_t__ dst0; int /*<<< orphan*/  srcrt; int /*<<< orphan*/  lastopt; } ;
struct TYPE_12__ {int accept_source_route; } ;
struct inet6_dev {TYPE_3__ cnf; } ;
struct in6_addr {int dummy; } ;
struct TYPE_15__ {int flags; } ;
struct TYPE_14__ {int hop_limit; struct in6_addr daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_13__ {TYPE_7__* dev; scalar_t__ error; } ;
struct TYPE_10__ {int accept_source_route; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 scalar_t__ CHECKSUM_NONE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ICMPV6_EXC_HOPLIMIT ; 
 int /*<<< orphan*/  ICMPV6_HDR_FIELD ; 
 int /*<<< orphan*/  ICMPV6_TIME_EXCEED ; 
 int IFF_LOOPBACK ; 
 struct inet6_skb_parm* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP6_INC_STATS_BH (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_ROUTING ; 
 int /*<<< orphan*/  IPSTATS_MIB_INADDRERRORS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INHDRERRORS ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
#define  IPV6_SRCRT_TYPE_2 128 
 scalar_t__ PACKET_HOST ; 
 struct net* dev_net (TYPE_7__*) ; 
 int /*<<< orphan*/  dst_input (struct sk_buff*) ; 
 int /*<<< orphan*/  icmpv6_param_prob (struct sk_buff*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 struct inet6_dev* in6_dev_get (TYPE_7__*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  ip6_dst_idev (TYPE_4__*) ; 
 int /*<<< orphan*/  ip6_route_input (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (struct in6_addr*,struct in6_addr*) ; 
 scalar_t__ ipv6_addr_is_multicast (struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_chk_home_addr (struct net*,struct in6_addr*) ; 
 TYPE_5__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 TYPE_4__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int* skb_transport_header (struct sk_buff*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm6_input_addr (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipv6_rthdr_rcv(struct sk_buff *skb)
{
	struct inet6_skb_parm *opt = IP6CB(skb);
	struct in6_addr *addr = NULL;
	struct in6_addr daddr;
	struct inet6_dev *idev;
	int n, i;
	struct ipv6_rt_hdr *hdr;
	struct rt0_hdr *rthdr;
	struct net *net = dev_net(skb->dev);
	int accept_source_route = net->ipv6.devconf_all->accept_source_route;

	idev = in6_dev_get(skb->dev);
	if (idev) {
		if (accept_source_route > idev->cnf.accept_source_route)
			accept_source_route = idev->cnf.accept_source_route;
		in6_dev_put(idev);
	}

	if (!pskb_may_pull(skb, skb_transport_offset(skb) + 8) ||
	    !pskb_may_pull(skb, (skb_transport_offset(skb) +
				 ((skb_transport_header(skb)[1] + 1) << 3)))) {
		IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
				 IPSTATS_MIB_INHDRERRORS);
		kfree_skb(skb);
		return -1;
	}

	hdr = (struct ipv6_rt_hdr *)skb_transport_header(skb);

	if (ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr) ||
	    skb->pkt_type != PACKET_HOST) {
		IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
				 IPSTATS_MIB_INADDRERRORS);
		kfree_skb(skb);
		return -1;
	}

looped_back:
	if (hdr->segments_left == 0) {
		switch (hdr->type) {
#if defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
		case IPV6_SRCRT_TYPE_2:
			/* Silently discard type 2 header unless it was
			 * processed by own
			 */
			if (!addr) {
				IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
						 IPSTATS_MIB_INADDRERRORS);
				kfree_skb(skb);
				return -1;
			}
			break;
#endif
		default:
			break;
		}

		opt->lastopt = opt->srcrt = skb_network_header_len(skb);
		skb->transport_header += (hdr->hdrlen + 1) << 3;
		opt->dst0 = opt->dst1;
		opt->dst1 = 0;
		opt->nhoff = (&hdr->nexthdr) - skb_network_header(skb);
		return 1;
	}

	switch (hdr->type) {
#if defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
	case IPV6_SRCRT_TYPE_2:
		if (accept_source_route < 0)
			goto unknown_rh;
		/* Silently discard invalid RTH type 2 */
		if (hdr->hdrlen != 2 || hdr->segments_left != 1) {
			IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
					 IPSTATS_MIB_INHDRERRORS);
			kfree_skb(skb);
			return -1;
		}
		break;
#endif
	default:
		goto unknown_rh;
	}

	/*
	 *	This is the routing header forwarding algorithm from
	 *	RFC 2460, page 16.
	 */

	n = hdr->hdrlen >> 1;

	if (hdr->segments_left > n) {
		IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
				 IPSTATS_MIB_INHDRERRORS);
		icmpv6_param_prob(skb, ICMPV6_HDR_FIELD,
				  ((&hdr->segments_left) -
				   skb_network_header(skb)));
		return -1;
	}

	/* We are about to mangle packet header. Be careful!
	   Do not damage packets queued somewhere.
	 */
	if (skb_cloned(skb)) {
		/* the copy is a forwarded packet */
		if (pskb_expand_head(skb, 0, 0, GFP_ATOMIC)) {
			IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
					 IPSTATS_MIB_OUTDISCARDS);
			kfree_skb(skb);
			return -1;
		}
		hdr = (struct ipv6_rt_hdr *)skb_transport_header(skb);
	}

	if (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->ip_summed = CHECKSUM_NONE;

	i = n - --hdr->segments_left;

	rthdr = (struct rt0_hdr *) hdr;
	addr = rthdr->addr;
	addr += i - 1;

	switch (hdr->type) {
#if defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
	case IPV6_SRCRT_TYPE_2:
		if (xfrm6_input_addr(skb, (xfrm_address_t *)addr,
				     (xfrm_address_t *)&ipv6_hdr(skb)->saddr,
				     IPPROTO_ROUTING) < 0) {
			IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
					 IPSTATS_MIB_INADDRERRORS);
			kfree_skb(skb);
			return -1;
		}
		if (!ipv6_chk_home_addr(dev_net(skb_dst(skb)->dev), addr)) {
			IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
					 IPSTATS_MIB_INADDRERRORS);
			kfree_skb(skb);
			return -1;
		}
		break;
#endif
	default:
		break;
	}

	if (ipv6_addr_is_multicast(addr)) {
		IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
				 IPSTATS_MIB_INADDRERRORS);
		kfree_skb(skb);
		return -1;
	}

	ipv6_addr_copy(&daddr, addr);
	ipv6_addr_copy(addr, &ipv6_hdr(skb)->daddr);
	ipv6_addr_copy(&ipv6_hdr(skb)->daddr, &daddr);

	skb_dst_drop(skb);
	ip6_route_input(skb);
	if (skb_dst(skb)->error) {
		skb_push(skb, skb->data - skb_network_header(skb));
		dst_input(skb);
		return -1;
	}

	if (skb_dst(skb)->dev->flags&IFF_LOOPBACK) {
		if (ipv6_hdr(skb)->hop_limit <= 1) {
			IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)),
					 IPSTATS_MIB_INHDRERRORS);
			icmpv6_send(skb, ICMPV6_TIME_EXCEED, ICMPV6_EXC_HOPLIMIT,
				    0, skb->dev);
			kfree_skb(skb);
			return -1;
		}
		ipv6_hdr(skb)->hop_limit--;
		goto looped_back;
	}

	skb_push(skb, skb->data - skb_network_header(skb));
	dst_input(skb);
	return -1;

unknown_rh:
	IP6_INC_STATS_BH(net, ip6_dst_idev(skb_dst(skb)), IPSTATS_MIB_INHDRERRORS);
	icmpv6_param_prob(skb, ICMPV6_HDR_FIELD,
			  (&hdr->type) - skb_network_header(skb));
	return -1;
}