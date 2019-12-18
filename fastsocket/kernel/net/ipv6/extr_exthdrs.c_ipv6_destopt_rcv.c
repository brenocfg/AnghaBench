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
struct inet6_skb_parm {int /*<<< orphan*/  dst1; int /*<<< orphan*/  nhoff; int /*<<< orphan*/  lastopt; } ;
struct dst_entry {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 struct inet6_skb_parm* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP6_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_INHDRERRORS ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 struct dst_entry* dst_clone (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  ip6_dst_idev (struct dst_entry*) ; 
 scalar_t__ ip6_parse_tlv (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header_len (struct sk_buff*) ; 
 int* skb_transport_header (struct sk_buff*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  tlvprocdestopt_lst ; 

__attribute__((used)) static int ipv6_destopt_rcv(struct sk_buff *skb)
{
	struct inet6_skb_parm *opt = IP6CB(skb);
#if defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
	__u16 dstbuf;
#endif
	struct dst_entry *dst;

	if (!pskb_may_pull(skb, skb_transport_offset(skb) + 8) ||
	    !pskb_may_pull(skb, (skb_transport_offset(skb) +
				 ((skb_transport_header(skb)[1] + 1) << 3)))) {
		IP6_INC_STATS_BH(dev_net(skb_dst(skb)->dev), ip6_dst_idev(skb_dst(skb)),
				 IPSTATS_MIB_INHDRERRORS);
		kfree_skb(skb);
		return -1;
	}

	opt->lastopt = opt->dst1 = skb_network_header_len(skb);
#if defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
	dstbuf = opt->dst1;
#endif

	dst = dst_clone(skb_dst(skb));
	if (ip6_parse_tlv(tlvprocdestopt_lst, skb)) {
		dst_release(dst);
		skb->transport_header += (skb_transport_header(skb)[1] + 1) << 3;
		opt = IP6CB(skb);
#if defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
		opt->nhoff = dstbuf;
#else
		opt->nhoff = opt->dst1;
#endif
		return 1;
	}

	IP6_INC_STATS_BH(dev_net(dst->dev),
			 ip6_dst_idev(dst), IPSTATS_MIB_INHDRERRORS);
	dst_release(dst);
	return -1;
}