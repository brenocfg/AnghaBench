#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  len; scalar_t__ sk; int /*<<< orphan*/  protocol; } ;
struct net_device {int flags; } ;
struct ipv6_pinfo {scalar_t__ mc_loop; } ;
struct inet6_dev {int dummy; } ;
struct dst_entry {struct net_device* dev; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {scalar_t__ hop_limit; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_LOOPBACK ; 
 TYPE_2__* IP6CB (struct sk_buff*) ; 
 int IP6SKB_FORWARDED ; 
 int /*<<< orphan*/  IP6_INC_STATS (int /*<<< orphan*/ ,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP6_UPD_PO_STATS (int /*<<< orphan*/ ,struct inet6_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTMCAST ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_POST_ROUTING ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (scalar_t__) ; 
 int /*<<< orphan*/  ip6_dev_loopback_xmit ; 
 struct inet6_dev* ip6_dst_idev (struct dst_entry*) ; 
 int /*<<< orphan*/  ip6_output_finish ; 
 scalar_t__ ipv6_addr_is_multicast (int /*<<< orphan*/ *) ; 
 scalar_t__ ipv6_chk_mcast_addr (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ mroute6_socket (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static int ip6_output2(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct net_device *dev = dst->dev;

	skb->protocol = htons(ETH_P_IPV6);
	skb->dev = dev;

	if (ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr)) {
		struct ipv6_pinfo* np = skb->sk ? inet6_sk(skb->sk) : NULL;
		struct inet6_dev *idev = ip6_dst_idev(skb_dst(skb));

		if (!(dev->flags & IFF_LOOPBACK) && (!np || np->mc_loop) &&
		    ((mroute6_socket(dev_net(dev)) &&
		     !(IP6CB(skb)->flags & IP6SKB_FORWARDED)) ||
		     ipv6_chk_mcast_addr(dev, &ipv6_hdr(skb)->daddr,
					 &ipv6_hdr(skb)->saddr))) {
			struct sk_buff *newskb = skb_clone(skb, GFP_ATOMIC);

			/* Do not check for IFF_ALLMULTI; multicast routing
			   is not supported in any case.
			 */
			if (newskb)
				NF_HOOK(PF_INET6, NF_INET_POST_ROUTING, newskb,
					NULL, newskb->dev,
					ip6_dev_loopback_xmit);

			if (ipv6_hdr(skb)->hop_limit == 0) {
				IP6_INC_STATS(dev_net(dev), idev,
					      IPSTATS_MIB_OUTDISCARDS);
				kfree_skb(skb);
				return 0;
			}
		}

		IP6_UPD_PO_STATS(dev_net(dev), idev, IPSTATS_MIB_OUTMCAST,
				skb->len);
	}

	return NF_HOOK(PF_INET6, NF_INET_POST_ROUTING, skb, NULL, skb->dev,
		       ip6_output_finish);
}