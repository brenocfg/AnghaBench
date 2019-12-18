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
typedef  int u32 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__ dst; } ;
struct rtable {scalar_t__ rt_type; TYPE_2__ u; } ;
struct iphdr {int ihl; int /*<<< orphan*/  tos; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct ip_rt_acct {int /*<<< orphan*/  i_bytes; int /*<<< orphan*/  i_packets; int /*<<< orphan*/  o_bytes; int /*<<< orphan*/  o_packets; } ;
struct direct_tcp_stat {int /*<<< orphan*/  input_route_fast; int /*<<< orphan*/  input_route_slow; } ;
struct TYPE_6__ {int tclassid; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int ENETUNREACH ; 
 int /*<<< orphan*/  IPSTATS_MIB_INADDRERRORS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INBCAST ; 
 int /*<<< orphan*/  IPSTATS_MIB_INMCAST ; 
 int /*<<< orphan*/  IPSTATS_MIB_INNOROUTES ; 
 int /*<<< orphan*/  IP_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_UPD_PO_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int NET_RX_DROP ; 
 scalar_t__ RTN_BROADCAST ; 
 scalar_t__ RTN_MULTICAST ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  direct_tcp_stats ; 
 int dst_input (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ip_rcv_options (struct sk_buff*) ; 
 int ip_route_input (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_acct ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 void* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* skb_dst (struct sk_buff*) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ip_rcv_finish(struct sk_buff *skb)
{
	const struct iphdr *iph = ip_hdr(skb);
	struct rtable *rt;
	struct direct_tcp_stat *stat;

	stat = per_cpu_ptr(direct_tcp_stats, smp_processor_id());

	/*
	 *	Initialise the virtual path cache for the packet. It describes
	 *	how the packet travels inside Linux networking.
	 */

	if (skb_dst(skb) == NULL) {
		int err = ip_route_input(skb, iph->daddr, iph->saddr, iph->tos,
					 skb->dev);
		stat->input_route_slow++;
		//FPRINTK("Skb 0x%p needs to go through route lookup\n", skb);

		if (unlikely(err)) {
			if (err == -EHOSTUNREACH)
				IP_INC_STATS_BH(dev_net(skb->dev),
						IPSTATS_MIB_INADDRERRORS);
			else if (err == -ENETUNREACH)
				IP_INC_STATS_BH(dev_net(skb->dev),
						IPSTATS_MIB_INNOROUTES);
			goto drop;
		}
	} else {
		stat->input_route_fast++;
		//FPRINTK("Skb 0x%p has set dst cache 0x%p[%u]\n", skb, skb_dst(skb), atomic_read(&skb_dst(skb)->__refcnt));
	}

#ifdef CONFIG_NET_CLS_ROUTE
	if (unlikely(skb_dst(skb)->tclassid)) {
		struct ip_rt_acct *st = per_cpu_ptr(ip_rt_acct, smp_processor_id());
		u32 idx = skb_dst(skb)->tclassid;
		st[idx&0xFF].o_packets++;
		st[idx&0xFF].o_bytes += skb->len;
		st[(idx>>16)&0xFF].i_packets++;
		st[(idx>>16)&0xFF].i_bytes += skb->len;
	}
#endif

	if (iph->ihl > 5 && ip_rcv_options(skb))
		goto drop;

	rt = skb_rtable(skb);
	if (rt->rt_type == RTN_MULTICAST) {
		IP_UPD_PO_STATS_BH(dev_net(rt->u.dst.dev), IPSTATS_MIB_INMCAST,
				skb->len);
	} else if (rt->rt_type == RTN_BROADCAST)
		IP_UPD_PO_STATS_BH(dev_net(rt->u.dst.dev), IPSTATS_MIB_INBCAST,
				skb->len);

	return dst_input(skb);

drop:
	kfree_skb(skb);
	return NET_RX_DROP;
}