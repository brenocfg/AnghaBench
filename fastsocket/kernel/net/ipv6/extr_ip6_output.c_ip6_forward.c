#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {scalar_t__ len; TYPE_3__* dev; int /*<<< orphan*/  local_df; } ;
struct rt6_info {int rt6i_flags; } ;
struct TYPE_9__ {TYPE_1__* devconf_all; } ;
struct net {TYPE_2__ ipv6; } ;
struct neighbour {int /*<<< orphan*/  primary_key; } ;
struct in6_addr {int dummy; } ;
struct ipv6hdr {int hop_limit; int /*<<< orphan*/  saddr; struct in6_addr daddr; } ;
struct inet6_skb_parm {int ra; scalar_t__ srcrt; scalar_t__ frag_max_size; } ;
struct dst_entry {TYPE_3__* dev; struct neighbour* neighbour; } ;
struct TYPE_10__ {int /*<<< orphan*/  hard_header_len; } ;
struct TYPE_8__ {scalar_t__ forwarding; scalar_t__ proxy_ndp; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  ICMPV6_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMPV6_EXC_HOPLIMIT ; 
 int /*<<< orphan*/  ICMPV6_NOT_NEIGHBOUR ; 
 int /*<<< orphan*/  ICMPV6_PKT_TOOBIG ; 
 int /*<<< orphan*/  ICMPV6_TIME_EXCEED ; 
 struct inet6_skb_parm* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP6_INC_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP6_INC_STATS_BH (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_FRAGFAILS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INADDRERRORS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INDISCARDS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INHDRERRORS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INTOOBIGERRORS ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTFORWDATAGRAMS ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_LOOPBACK ; 
 int IPV6_ADDR_MULTICAST ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_FORWARD ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int RTF_GATEWAY ; 
 int /*<<< orphan*/  XFRM_POLICY_FWD ; 
 struct net* dev_net (TYPE_3__*) ; 
 scalar_t__ dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 scalar_t__ ip6_call_ra_chain (struct sk_buff*,int) ; 
 int /*<<< orphan*/  ip6_dst_idev (struct dst_entry*) ; 
 int /*<<< orphan*/  ip6_forward_finish ; 
 int ip6_forward_proxy_check (struct sk_buff*) ; 
 int ip6_input (struct sk_buff*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nd_tbl ; 
 int /*<<< orphan*/  ndisc_send_redirect (struct sk_buff*,struct neighbour*,struct in6_addr*) ; 
 scalar_t__ pneigh_lookup (int /*<<< orphan*/ *,struct net*,struct in6_addr*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_forward_csum (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int* skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_sec_path (struct sk_buff*) ; 
 scalar_t__ skb_warn_if_lro (struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm6_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm6_route_forward (struct sk_buff*) ; 
 scalar_t__ xrlim_allow (struct dst_entry*,int) ; 

int ip6_forward(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct ipv6hdr *hdr = ipv6_hdr(skb);
	struct inet6_skb_parm *opt = IP6CB(skb);
	struct net *net = dev_net(dst->dev);

	if (net->ipv6.devconf_all->forwarding == 0)
		goto error;

	if (skb_warn_if_lro(skb))
		goto drop;

	if (!xfrm6_policy_check(NULL, XFRM_POLICY_FWD, skb)) {
		IP6_INC_STATS(net, ip6_dst_idev(dst), IPSTATS_MIB_INDISCARDS);
		goto drop;
	}

	skb_forward_csum(skb);

	/*
	 *	We DO NOT make any processing on
	 *	RA packets, pushing them to user level AS IS
	 *	without ane WARRANTY that application will be able
	 *	to interpret them. The reason is that we
	 *	cannot make anything clever here.
	 *
	 *	We are not end-node, so that if packet contains
	 *	AH/ESP, we cannot make anything.
	 *	Defragmentation also would be mistake, RA packets
	 *	cannot be fragmented, because there is no warranty
	 *	that different fragments will go along one path. --ANK
	 */
	if (opt->ra) {
		u8 *ptr = skb_network_header(skb) + opt->ra;
		if (ip6_call_ra_chain(skb, (ptr[2]<<8) + ptr[3]))
			return 0;
	}

	/*
	 *	check and decrement ttl
	 */
	if (hdr->hop_limit <= 1) {
		/* Force OUTPUT device used as source address */
		skb->dev = dst->dev;
		icmpv6_send(skb, ICMPV6_TIME_EXCEED, ICMPV6_EXC_HOPLIMIT,
			    0, skb->dev);
		IP6_INC_STATS_BH(net,
				 ip6_dst_idev(dst), IPSTATS_MIB_INHDRERRORS);

		kfree_skb(skb);
		return -ETIMEDOUT;
	}

	/* XXX: idev->cnf.proxy_ndp? */
	if (net->ipv6.devconf_all->proxy_ndp &&
	    pneigh_lookup(&nd_tbl, net, &hdr->daddr, skb->dev, 0)) {
		int proxied = ip6_forward_proxy_check(skb);
		if (proxied > 0)
			return ip6_input(skb);
		else if (proxied < 0) {
			IP6_INC_STATS(net, ip6_dst_idev(dst),
				      IPSTATS_MIB_INDISCARDS);
			goto drop;
		}
	}

	if (!xfrm6_route_forward(skb)) {
		IP6_INC_STATS(net, ip6_dst_idev(dst), IPSTATS_MIB_INDISCARDS);
		goto drop;
	}
	dst = skb_dst(skb);

	/* IPv6 specs say nothing about it, but it is clear that we cannot
	   send redirects to source routed frames.
	   We don't send redirects to frames decapsulated from IPsec.
	 */
	if (skb->dev == dst->dev && dst->neighbour && opt->srcrt == 0 &&
	    !skb_sec_path(skb)) {
		struct in6_addr *target = NULL;
		struct rt6_info *rt;
		struct neighbour *n = dst->neighbour;

		/*
		 *	incoming and outgoing devices are the same
		 *	send a redirect.
		 */

		rt = (struct rt6_info *) dst;
		if ((rt->rt6i_flags & RTF_GATEWAY))
			target = (struct in6_addr*)&n->primary_key;
		else
			target = &hdr->daddr;

		/* Limit redirects both by destination (here)
		   and by source (inside ndisc_send_redirect)
		 */
		if (xrlim_allow(dst, 1*HZ))
			ndisc_send_redirect(skb, n, target);
	} else {
		int addrtype = ipv6_addr_type(&hdr->saddr);

		/* This check is security critical. */
		if (addrtype == IPV6_ADDR_ANY ||
		    addrtype & (IPV6_ADDR_MULTICAST | IPV6_ADDR_LOOPBACK))
			goto error;
		if (addrtype & IPV6_ADDR_LINKLOCAL) {
			icmpv6_send(skb, ICMPV6_DEST_UNREACH,
				ICMPV6_NOT_NEIGHBOUR, 0, skb->dev);
			goto error;
		}
	}

	if ((!skb->local_df && skb->len > dst_mtu(dst) && !skb_is_gso(skb)) ||
	    (IP6CB(skb)->frag_max_size && IP6CB(skb)->frag_max_size > dst_mtu(dst))) {
		/* Again, force OUTPUT device used as source address */
		skb->dev = dst->dev;
		icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, dst_mtu(dst), skb->dev);
		IP6_INC_STATS_BH(net,
				 ip6_dst_idev(dst), IPSTATS_MIB_INTOOBIGERRORS);
		IP6_INC_STATS_BH(net,
				 ip6_dst_idev(dst), IPSTATS_MIB_FRAGFAILS);
		kfree_skb(skb);
		return -EMSGSIZE;
	}

	if (skb_cow(skb, dst->dev->hard_header_len)) {
		IP6_INC_STATS(net, ip6_dst_idev(dst), IPSTATS_MIB_OUTDISCARDS);
		goto drop;
	}

	hdr = ipv6_hdr(skb);

	/* Mangling hops number delayed to point after skb COW */

	hdr->hop_limit--;

	IP6_INC_STATS_BH(net, ip6_dst_idev(dst), IPSTATS_MIB_OUTFORWDATAGRAMS);
	return NF_HOOK(PF_INET6, NF_INET_FORWARD, skb, skb->dev, dst->dev,
		       ip6_forward_finish);

error:
	IP6_INC_STATS_BH(net, ip6_dst_idev(dst), IPSTATS_MIB_INADDRERRORS);
drop:
	kfree_skb(skb);
	return -EINVAL;
}