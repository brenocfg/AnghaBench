#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {scalar_t__ mark; } ;
struct TYPE_9__ {struct net_device* dev; int /*<<< orphan*/  rt_next; } ;
struct TYPE_8__ {TYPE_3__ dst; } ;
struct TYPE_7__ {int fl4_dst; int fl4_src; int iif; int oif; int fl4_tos; scalar_t__ mark; } ;
struct rtable {TYPE_2__ u; TYPE_1__ fl; } ;
struct net_device {int ifindex; } ;
struct net {int dummy; } ;
struct in_device {int dummy; } ;
typedef  int __be32 ;
struct TYPE_11__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_10__ {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IN_DEV_MFORWARD (struct in_device*) ; 
 int IPTOS_RT_MASK ; 
 int /*<<< orphan*/  RT_CACHE_STAT_INC (int /*<<< orphan*/ ) ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dst_use (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_hit ; 
 int /*<<< orphan*/  in_hlist_search ; 
 int ip_check_mc (struct in_device*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_5__* ip_hdr (struct sk_buff*) ; 
 int ip_route_input_mc (struct sk_buff*,int,int,int,struct net_device*,int) ; 
 int ip_route_input_slow (struct sk_buff*,int,int,int,struct net_device*) ; 
 int /*<<< orphan*/  ipv4_is_local_multicast (int) ; 
 scalar_t__ ipv4_is_multicast (int) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ net_eq (struct net*,struct net*) ; 
 struct rtable* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rt_caching (struct net*) ; 
 int /*<<< orphan*/  rt_genid (struct net*) ; 
 unsigned int rt_hash (int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* rt_hash_table ; 
 int /*<<< orphan*/  rt_is_expired (struct rtable*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,TYPE_3__*) ; 

int ip_route_input(struct sk_buff *skb, __be32 daddr, __be32 saddr,
		   u8 tos, struct net_device *dev)
{
	struct rtable * rth;
	unsigned	hash;
	int iif = dev->ifindex;
	struct net *net;

	net = dev_net(dev);

	if (!rt_caching(net))
		goto skip_cache;

	tos &= IPTOS_RT_MASK;
	hash = rt_hash(daddr, saddr, iif, rt_genid(net));

	rcu_read_lock();
	for (rth = rcu_dereference(rt_hash_table[hash].chain); rth;
	     rth = rcu_dereference(rth->u.dst.rt_next)) {
		if (((rth->fl.fl4_dst ^ daddr) |
		     (rth->fl.fl4_src ^ saddr) |
		     (rth->fl.iif ^ iif) |
		     rth->fl.oif |
		     (rth->fl.fl4_tos ^ tos)) == 0 &&
		    rth->fl.mark == skb->mark &&
		    net_eq(dev_net(rth->u.dst.dev), net) &&
		    !rt_is_expired(rth)) {
			dst_use(&rth->u.dst, jiffies);
			RT_CACHE_STAT_INC(in_hit);
			rcu_read_unlock();
			skb_dst_set(skb, &rth->u.dst);
			return 0;
		}
		RT_CACHE_STAT_INC(in_hlist_search);
	}
	rcu_read_unlock();

skip_cache:
	/* Multicast recognition logic is moved from route cache to here.
	   The problem was that too many Ethernet cards have broken/missing
	   hardware multicast filters :-( As result the host on multicasting
	   network acquires a lot of useless route cache entries, sort of
	   SDR messages from all the world. Now we try to get rid of them.
	   Really, provided software IP multicast filter is organized
	   reasonably (at least, hashed), it does not result in a slowdown
	   comparing with route cache reject entries.
	   Note, that multicast routers are not affected, because
	   route cache entry is created eventually.
	 */
	if (ipv4_is_multicast(daddr)) {
		struct in_device *in_dev;

		rcu_read_lock();
		if ((in_dev = __in_dev_get_rcu(dev)) != NULL) {
			int our = ip_check_mc(in_dev, daddr, saddr,
				ip_hdr(skb)->protocol);
			if (our
#ifdef CONFIG_IP_MROUTE
			    || (!ipv4_is_local_multicast(daddr) &&
				IN_DEV_MFORWARD(in_dev))
#endif
			    ) {
				rcu_read_unlock();
				return ip_route_input_mc(skb, daddr, saddr,
							 tos, dev, our);
			}
		}
		rcu_read_unlock();
		return -EINVAL;
	}
	return ip_route_input_slow(skb, daddr, saddr, tos, dev);
}