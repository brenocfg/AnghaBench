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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {struct sock* v6_ctl_sk; } ;
struct net {TYPE_1__ dccp; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct flowi {int /*<<< orphan*/  fl_ip_sport; int /*<<< orphan*/  fl_ip_dport; int /*<<< orphan*/  oif; int /*<<< orphan*/  proto; int /*<<< orphan*/  fl6_src; int /*<<< orphan*/  fl6_dst; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  fl ;
struct TYPE_6__ {scalar_t__ dccph_type; int /*<<< orphan*/  dccph_sport; int /*<<< orphan*/  dccph_dport; int /*<<< orphan*/  dccph_checksum; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_INC_STATS_BH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_MIB_OUTRSTS ; 
 int /*<<< orphan*/  DCCP_MIB_OUTSEGS ; 
 scalar_t__ DCCP_PKT_RESET ; 
 int /*<<< orphan*/  IPPROTO_DCCP ; 
 struct sk_buff* dccp_ctl_make_reset (struct sock*,struct sk_buff*) ; 
 TYPE_3__* dccp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_v6_csum_finish (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_dst_lookup (struct sock*,struct dst_entry**,struct flowi*) ; 
 int /*<<< orphan*/  ip6_xmit (struct sock*,struct sk_buff*,struct flowi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_unicast_destination (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_skb_classify_flow (struct sk_buff*,struct flowi*) ; 
 TYPE_2__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 scalar_t__ xfrm_lookup (struct net*,struct dst_entry**,struct flowi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dccp_v6_ctl_send_reset(struct sock *sk, struct sk_buff *rxskb)
{
	struct ipv6hdr *rxip6h;
	struct sk_buff *skb;
	struct flowi fl;
	struct net *net = dev_net(skb_dst(rxskb)->dev);
	struct sock *ctl_sk = net->dccp.v6_ctl_sk;
	struct dst_entry *dst;

	if (dccp_hdr(rxskb)->dccph_type == DCCP_PKT_RESET)
		return;

	if (!ipv6_unicast_destination(rxskb))
		return;

	skb = dccp_ctl_make_reset(ctl_sk, rxskb);
	if (skb == NULL)
		return;

	rxip6h = ipv6_hdr(rxskb);
	dccp_hdr(skb)->dccph_checksum = dccp_v6_csum_finish(skb, &rxip6h->saddr,
							    &rxip6h->daddr);

	memset(&fl, 0, sizeof(fl));
	ipv6_addr_copy(&fl.fl6_dst, &rxip6h->saddr);
	ipv6_addr_copy(&fl.fl6_src, &rxip6h->daddr);

	fl.proto = IPPROTO_DCCP;
	fl.oif = inet6_iif(rxskb);
	fl.fl_ip_dport = dccp_hdr(skb)->dccph_dport;
	fl.fl_ip_sport = dccp_hdr(skb)->dccph_sport;
	security_skb_classify_flow(rxskb, &fl);

	/* sk = NULL, but it is safe for now. RST socket required. */
	if (!ip6_dst_lookup(ctl_sk, &dst, &fl)) {
		if (xfrm_lookup(net, &dst, &fl, NULL, 0) >= 0) {
			skb_dst_set(skb, dst);
			ip6_xmit(ctl_sk, skb, &fl, NULL, 0);
			DCCP_INC_STATS_BH(DCCP_MIB_OUTSEGS);
			DCCP_INC_STATS_BH(DCCP_MIB_OUTRSTS);
			return;
		}
	}

	kfree_skb(skb);
}