#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct inet6_protocol {int flags; int (* handler ) (struct sk_buff*) ;} ;
struct inet6_dev {int dummy; } ;
struct TYPE_5__ {unsigned int nhoff; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_PARAMPROB ; 
 int /*<<< orphan*/  ICMPV6_UNK_NEXTHDR ; 
 int INET6_PROTO_FINAL ; 
 int INET6_PROTO_NOPOLICY ; 
 TYPE_3__* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP6_INC_STATS_BH (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_INDELIVERS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INDISCARDS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INUNKNOWNPROTOS ; 
 int MAX_INET_PROTOS ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inet6_protos ; 
 struct inet6_dev* ip6_dst_idev (TYPE_1__*) ; 
 scalar_t__ ipv6_addr_is_multicast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_chk_mcast_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_is_mld (struct sk_buff*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int raw6_local_deliver (struct sk_buff*,int) ; 
 struct inet6_protocol* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 
 int* skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_transport_offset (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 
 scalar_t__ xfrm6_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int ip6_input_finish(struct sk_buff *skb)
{
	const struct inet6_protocol *ipprot;
	unsigned int nhoff;
	int nexthdr, raw;
	u8 hash;
	struct inet6_dev *idev;
	struct net *net = dev_net(skb_dst(skb)->dev);

	/*
	 *	Parse extension headers
	 */

	rcu_read_lock();
resubmit:
	idev = ip6_dst_idev(skb_dst(skb));
	if (!pskb_pull(skb, skb_transport_offset(skb)))
		goto discard;
	nhoff = IP6CB(skb)->nhoff;
	nexthdr = skb_network_header(skb)[nhoff];

	raw = raw6_local_deliver(skb, nexthdr);

	hash = nexthdr & (MAX_INET_PROTOS - 1);
	if ((ipprot = rcu_dereference(inet6_protos[hash])) != NULL) {
		int ret;

		if (ipprot->flags & INET6_PROTO_FINAL) {
			struct ipv6hdr *hdr;

			/* Free reference early: we don't need it any more,
			   and it may hold ip_conntrack module loaded
			   indefinitely. */
			nf_reset(skb);

			skb_postpull_rcsum(skb, skb_network_header(skb),
					   skb_network_header_len(skb));
			hdr = ipv6_hdr(skb);
			if (ipv6_addr_is_multicast(&hdr->daddr) &&
			    !ipv6_chk_mcast_addr(skb->dev, &hdr->daddr,
			    &hdr->saddr) &&
			    !ipv6_is_mld(skb, nexthdr))
				goto discard;
		}
		if (!(ipprot->flags & INET6_PROTO_NOPOLICY) &&
		    !xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb))
			goto discard;

		ret = ipprot->handler(skb);
		if (ret > 0)
			goto resubmit;
		else if (ret == 0)
			IP6_INC_STATS_BH(net, idev, IPSTATS_MIB_INDELIVERS);
	} else {
		if (!raw) {
			if (xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb)) {
				IP6_INC_STATS_BH(net, idev,
						 IPSTATS_MIB_INUNKNOWNPROTOS);
				icmpv6_send(skb, ICMPV6_PARAMPROB,
					    ICMPV6_UNK_NEXTHDR, nhoff,
					    skb->dev);
			}
		} else
			IP6_INC_STATS_BH(net, idev, IPSTATS_MIB_INDELIVERS);
		kfree_skb(skb);
	}
	rcu_read_unlock();
	return 0;

discard:
	IP6_INC_STATS_BH(net, idev, IPSTATS_MIB_INDISCARDS);
	rcu_read_unlock();
	kfree_skb(skb);
	return 0;
}