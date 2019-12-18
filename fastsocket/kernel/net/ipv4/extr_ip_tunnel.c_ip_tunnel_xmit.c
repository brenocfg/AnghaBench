#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {int protocol; scalar_t__ data; } ;
struct TYPE_14__ {int header_len; struct net_device* dev; } ;
struct TYPE_10__ {TYPE_7__ dst; } ;
struct rtable {scalar_t__ rt_gateway; TYPE_3__ u; } ;
struct TYPE_13__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_fifo_errors; } ;
struct net_device {unsigned int needed_headroom; TYPE_6__ stats; } ;
struct neighbour {int /*<<< orphan*/  primary_key; } ;
struct ipv6hdr {int hop_limit; } ;
struct iphdr {scalar_t__ daddr; int tos; int frag_off; int ttl; int /*<<< orphan*/  saddr; } ;
struct TYPE_8__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_9__ {int /*<<< orphan*/  link; int /*<<< orphan*/  o_key; TYPE_1__ iph; } ;
struct ip_tunnel {scalar_t__ err_count; scalar_t__ err_time; TYPE_2__ parms; scalar_t__ hlen; } ;
struct in6_addr {scalar_t__* s6_addr32; } ;
struct flowi {int /*<<< orphan*/  fl4_dst; int /*<<< orphan*/  fl4_src; } ;
typedef  scalar_t__ __be32 ;
typedef  int __be16 ;
struct TYPE_12__ {struct in6_addr daddr; } ;
struct TYPE_11__ {struct neighbour* neighbour; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IPTUNNEL_ERR_TIMEO ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_COMPATv4 ; 
 int /*<<< orphan*/  IP_DF ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int LL_RESERVED_SPACE (struct net_device*) ; 
 int /*<<< orphan*/  RTAX_HOPLIMIT ; 
 int /*<<< orphan*/  RT_TOS (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dst_link_failure (struct sk_buff*) ; 
 int dst_metric (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct rtable* ip_route_output_tunnel (int /*<<< orphan*/ ,struct flowi*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  ip_tunnel_ecn_encap (int,struct iphdr const*,struct sk_buff*) ; 
 int iptunnel_xmit (int /*<<< orphan*/ ,struct rtable*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int,int,struct iphdr const*) ; 
 int /*<<< orphan*/  iptunnel_xmit_stats (int,TYPE_6__*) ; 
 int ipv6_addr_type (struct in6_addr const*) ; 
 int ipv6_get_dsfield (struct ipv6hdr const*) ; 
 TYPE_5__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,unsigned int) ; 
 TYPE_4__* skb_dst (struct sk_buff*) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tnl_update_pmtu (struct net_device*,struct sk_buff*,struct rtable*,int) ; 

void ip_tunnel_xmit(struct sk_buff *skb, struct net_device *dev,
		    const struct iphdr *tnl_params, const u8 protocol)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	const struct iphdr *inner_iph;
	struct flowi fl4;
	u8     tos, ttl;
	__be16 df;
	struct rtable *rt;		/* Route to the other host */
	unsigned int max_headroom;	/* The extra header space needed */
	__be32 dst;
	int err;

	/* inner_iph = (const struct iphdr *)skb_inner_network_header(skb); */
	inner_iph = (const struct iphdr *)(skb->data + tunnel->hlen);

	dst = tnl_params->daddr;
	if (dst == 0) {
		/* NBMA tunnel */

		if (skb_dst(skb) == NULL) {
			dev->stats.tx_fifo_errors++;
			goto tx_error;
		}

		if (skb->protocol == htons(ETH_P_IP)) {
			rt = skb_rtable(skb);
			if (rt->rt_gateway)
				dst = rt->rt_gateway;
			else
				dst = inner_iph->daddr;
		}
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
		else if (skb->protocol == htons(ETH_P_IPV6)) {
			const struct in6_addr *addr6;
			struct neighbour *neigh;
			bool do_tx_error_icmp;
			int addr_type;

			neigh = skb_dst(skb)->neighbour;
			if (neigh == NULL)
				goto tx_error;

			addr6 = (const struct in6_addr *)&neigh->primary_key;
			addr_type = ipv6_addr_type(addr6);

			if (addr_type == IPV6_ADDR_ANY) {
				addr6 = &ipv6_hdr(skb)->daddr;
				addr_type = ipv6_addr_type(addr6);
			}

			if ((addr_type & IPV6_ADDR_COMPATv4) == 0)
				do_tx_error_icmp = true;
			else {
				do_tx_error_icmp = false;
				dst = addr6->s6_addr32[3];
			}
			neigh_release(neigh);
			if (do_tx_error_icmp)
				goto tx_error_icmp;
		}
#endif
		else
			goto tx_error;
	}

	tos = tnl_params->tos;
	if (tos & 0x1) {
		tos &= ~0x1;
		if (skb->protocol == htons(ETH_P_IP))
			tos = inner_iph->tos;
		else if (skb->protocol == htons(ETH_P_IPV6))
			tos = ipv6_get_dsfield((const struct ipv6hdr *)inner_iph);
	}

	rt = ip_route_output_tunnel(dev_net(dev), &fl4,
				    tunnel->parms.iph.protocol,
				    dst, tnl_params->saddr,
				    tunnel->parms.o_key,
				    RT_TOS(tos),
				    tunnel->parms.link);
	if (IS_ERR(rt)) {
		dev->stats.tx_carrier_errors++;
		goto tx_error;
	}
	if (rt->u.dst.dev == dev) {
		ip_rt_put(rt);
		dev->stats.collisions++;
		goto tx_error;
	}

	if (tnl_update_pmtu(dev, skb, rt, tnl_params->frag_off)) {
		ip_rt_put(rt);
		goto tx_error;
	}

	if (tunnel->err_count > 0) {
		if (time_before(jiffies,
				tunnel->err_time + IPTUNNEL_ERR_TIMEO)) {
			tunnel->err_count--;

			dst_link_failure(skb);
		} else
			tunnel->err_count = 0;
	}

	ttl = tnl_params->ttl;
	if (ttl == 0) {
		if (skb->protocol == htons(ETH_P_IP))
			ttl = inner_iph->ttl;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
		else if (skb->protocol == htons(ETH_P_IPV6))
			ttl = ((const struct ipv6hdr *)inner_iph)->hop_limit;
#endif
		else
			ttl = dst_metric(&rt->u.dst, RTAX_HOPLIMIT);
	}

	df = tnl_params->frag_off;
	if (skb->protocol == htons(ETH_P_IP))
		df |= (inner_iph->frag_off&htons(IP_DF));

	max_headroom = LL_RESERVED_SPACE(rt->u.dst.dev) + sizeof(struct iphdr)
			+ rt->u.dst.header_len;
	if (max_headroom > dev->needed_headroom) {
		dev->needed_headroom = max_headroom;
		if (skb_cow_head(skb, dev->needed_headroom)) {
			dev->stats.tx_dropped++;
			dev_kfree_skb(skb);
			return;
		}
	}

	err = iptunnel_xmit(dev_net(dev), rt, skb,
			    fl4.fl4_src, fl4.fl4_dst, protocol,
			    ip_tunnel_ecn_encap(tos, inner_iph, skb), ttl, df,
			    inner_iph);
	iptunnel_xmit_stats(err, &dev->stats);
	return;

#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
tx_error_icmp:
	dst_link_failure(skb);
#endif
tx_error:
	dev->stats.tx_errors++;
	dev_kfree_skb(skb);
}