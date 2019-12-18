#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_2__ {struct sock* ndisc_sk; } ;
struct net {TYPE_1__ ipv6; } ;
struct neighbour {int dummy; } ;
struct inet6_dev {int dummy; } ;
struct in6_addr {int dummy; } ;
struct icmp6hdr {int /*<<< orphan*/  icmp6_type; } ;
struct flowi {int dummy; } ;
struct dst_entry {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6MSGOUT_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP6_MIB_OUTMSGS ; 
 int /*<<< orphan*/  IP6_UPD_PO_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUT ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_LOCAL_OUT ; 
 int /*<<< orphan*/  PF_INET6 ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dst_output ; 
 struct dst_entry* icmp6_dst_alloc (struct net_device*,struct neighbour*,struct in6_addr const*) ; 
 int /*<<< orphan*/  icmpv6_flow_init (struct sock*,struct flowi*,int /*<<< orphan*/ ,struct in6_addr const*,struct in6_addr const*,int /*<<< orphan*/ ) ; 
 struct inet6_dev* in6_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 int xfrm_lookup (struct net*,struct dst_entry**,struct flowi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ndisc_send_skb(struct sk_buff *skb,
		    struct net_device *dev,
		    struct neighbour *neigh,
		    const struct in6_addr *daddr,
		    const struct in6_addr *saddr,
		    struct icmp6hdr *icmp6h)
{
	struct flowi fl;
	struct dst_entry *dst;
	struct net *net = dev_net(dev);
	struct sock *sk = net->ipv6.ndisc_sk;
	struct inet6_dev *idev;
	int err;
	u8 type;

	type = icmp6h->icmp6_type;

	icmpv6_flow_init(sk, &fl, type, saddr, daddr, dev->ifindex);

	dst = icmp6_dst_alloc(dev, neigh, daddr);
	if (!dst) {
		kfree_skb(skb);
		return;
	}

	err = xfrm_lookup(net, &dst, &fl, NULL, 0);
	if (err < 0) {
		kfree_skb(skb);
		return;
	}

	skb_dst_set(skb, dst);

	idev = in6_dev_get(dst->dev);
	IP6_UPD_PO_STATS(net, idev, IPSTATS_MIB_OUT, skb->len);

	err = NF_HOOK(PF_INET6, NF_INET_LOCAL_OUT, skb, NULL, dst->dev,
		      dst_output);
	if (!err) {
		ICMP6MSGOUT_INC_STATS(net, idev, type);
		ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTMSGS);
	}

	if (likely(idev != NULL))
		in6_dev_put(idev);
}