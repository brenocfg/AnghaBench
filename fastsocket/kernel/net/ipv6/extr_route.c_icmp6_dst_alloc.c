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
struct dst_entry {int* metrics; struct dst_entry* next; int /*<<< orphan*/  flags; int /*<<< orphan*/  output; int /*<<< orphan*/  __refcnt; } ;
struct TYPE_6__ {struct dst_entry dst; } ;
struct TYPE_5__ {int plen; int /*<<< orphan*/  addr; } ;
struct rt6_info {TYPE_3__ u; TYPE_2__ rt6i_dst; struct net_device* rt6i_dev; struct neighbour* rt6i_nexthop; struct inet6_dev* rt6i_idev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip6_dst_ops; } ;
struct net {TYPE_1__ ipv6; } ;
struct neighbour {int dummy; } ;
struct inet6_dev {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_HOST ; 
 int IPV6_ADDR_UNICAST ; 
 scalar_t__ IS_ERR (struct neighbour*) ; 
 int RTAX_ADVMSS ; 
 int RTAX_HOPLIMIT ; 
 int RTAX_MTU ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  fib6_force_start_gc (struct net*) ; 
 struct dst_entry* icmp6_dst_gc_list ; 
 int /*<<< orphan*/  icmp6_dst_lock ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 struct rt6_info* ip6_dst_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_output ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 int ipv6_addr_type (struct in6_addr const*) ; 
 int ipv6_advmss (struct net*,int /*<<< orphan*/ ) ; 
 int ipv6_get_mtu (struct net_device*) ; 
 struct neighbour* ndisc_get_neigh (struct net_device*,struct in6_addr const*) ; 
 int /*<<< orphan*/  neigh_hold (struct neighbour*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct dst_entry *icmp6_dst_alloc(struct net_device *dev,
				  struct neighbour *neigh,
				  const struct in6_addr *addr)
{
	struct rt6_info *rt;
	struct inet6_dev *idev = in6_dev_get(dev);
	struct net *net = dev_net(dev);

	if (unlikely(idev == NULL))
		return NULL;

	rt = ip6_dst_alloc(&net->ipv6.ip6_dst_ops);
	if (unlikely(rt == NULL)) {
		in6_dev_put(idev);
		goto out;
	}

	dev_hold(dev);
	if (neigh)
		neigh_hold(neigh);
	else {
		neigh = ndisc_get_neigh(dev, addr);
		if (IS_ERR(neigh))
			neigh = NULL;
	}

	rt->rt6i_dev	  = dev;
	rt->rt6i_idev     = idev;
	rt->rt6i_nexthop  = neigh;
	atomic_set(&rt->u.dst.__refcnt, 1);
	rt->u.dst.metrics[RTAX_HOPLIMIT-1] = 255;
	rt->u.dst.metrics[RTAX_MTU-1] = ipv6_get_mtu(rt->rt6i_dev);
	rt->u.dst.metrics[RTAX_ADVMSS-1] = ipv6_advmss(net, dst_mtu(&rt->u.dst));
	rt->u.dst.output  = ip6_output;

#if 0	/* there's no chance to use these for ndisc */
	rt->u.dst.flags   = ipv6_addr_type(addr) & IPV6_ADDR_UNICAST
				? DST_HOST
				: 0;
	ipv6_addr_copy(&rt->rt6i_dst.addr, addr);
	rt->rt6i_dst.plen = 128;
#endif

	spin_lock_bh(&icmp6_dst_lock);
	rt->u.dst.next = icmp6_dst_gc_list;
	icmp6_dst_gc_list = &rt->u.dst;
	spin_unlock_bh(&icmp6_dst_lock);

	fib6_force_start_gc(net);

out:
	return &rt->u.dst;
}