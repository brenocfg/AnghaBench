#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  mark; } ;
struct TYPE_6__ {int obsolete; int /*<<< orphan*/  input; struct net_device* dev; int /*<<< orphan*/  tclassid; int /*<<< orphan*/  flags; int /*<<< orphan*/  __refcnt; int /*<<< orphan*/  output; } ;
struct TYPE_7__ {TYPE_2__ dst; } ;
struct TYPE_5__ {scalar_t__ oif; int /*<<< orphan*/  iif; void* fl4_src; int /*<<< orphan*/  mark; int /*<<< orphan*/  fl4_tos; void* fl4_dst; } ;
struct rtable {TYPE_3__ u; int /*<<< orphan*/  rt_flags; int /*<<< orphan*/  rt_type; int /*<<< orphan*/  rt_genid; void* rt_spec_dst; void* rt_gateway; TYPE_1__ fl; void* idev; int /*<<< orphan*/  rt_iif; void* rt_src; void* rt_dst; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct in_device {int dummy; } ;
typedef  void* __be32 ;
struct TYPE_8__ {struct net_device* loopback_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_HOST ; 
 int /*<<< orphan*/  DST_NOPOLICY ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ IN_DEV_CONF_GET (struct in_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ IN_DEV_MFORWARD (struct in_device*) ; 
 int /*<<< orphan*/  IN_DEV_ROUTE_LOCALNET (struct in_device*) ; 
 int /*<<< orphan*/  NOPOLICY ; 
 int /*<<< orphan*/  RTCF_LOCAL ; 
 int /*<<< orphan*/  RTCF_MULTICAST ; 
 int /*<<< orphan*/  RTN_MULTICAST ; 
 int /*<<< orphan*/  RT_CACHE_STAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_SCOPE_LINK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct rtable* dst_alloc (int /*<<< orphan*/ *) ; 
 scalar_t__ fib_validate_source (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 void* in_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in_dev_put (struct in_device*) ; 
 int /*<<< orphan*/  in_slow_mc ; 
 void* inet_select_addr (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ init_net ; 
 int /*<<< orphan*/  ip_local_deliver ; 
 int /*<<< orphan*/  ip_mr_input ; 
 int /*<<< orphan*/  ip_rt_bug ; 
 int /*<<< orphan*/  ipv4_dst_ops ; 
 scalar_t__ ipv4_is_lbcast (void*) ; 
 int /*<<< orphan*/  ipv4_is_local_multicast (void*) ; 
 scalar_t__ ipv4_is_loopback (void*) ; 
 scalar_t__ ipv4_is_multicast (void*) ; 
 scalar_t__ ipv4_is_zeronet (void*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rt_genid (int /*<<< orphan*/ ) ; 
 unsigned int rt_hash (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt_intern_hash (unsigned int,struct rtable*,int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int ip_route_input_mc(struct sk_buff *skb, __be32 daddr, __be32 saddr,
				u8 tos, struct net_device *dev, int our)
{
	unsigned hash;
	struct rtable *rth;
	__be32 spec_dst;
	struct in_device *in_dev = in_dev_get(dev);
	u32 itag = 0;

	/* Primary sanity checks. */

	if (in_dev == NULL)
		return -EINVAL;

	if (ipv4_is_multicast(saddr) || ipv4_is_lbcast(saddr) ||
	    skb->protocol != htons(ETH_P_IP))
		goto e_inval;

	if (likely(!IN_DEV_ROUTE_LOCALNET(in_dev)))
		if (ipv4_is_loopback(saddr))
			goto e_inval;

	if (ipv4_is_zeronet(saddr)) {
		if (!ipv4_is_local_multicast(daddr))
			goto e_inval;
		spec_dst = inet_select_addr(dev, 0, RT_SCOPE_LINK);
	} else if (fib_validate_source(saddr, 0, tos, 0,
					dev, &spec_dst, &itag, 0) < 0)
		goto e_inval;

	rth = dst_alloc(&ipv4_dst_ops);
	if (!rth)
		goto e_nobufs;

	rth->u.dst.output = ip_rt_bug;
	rth->u.dst.obsolete = -1;

	atomic_set(&rth->u.dst.__refcnt, 1);
	rth->u.dst.flags= DST_HOST;
	if (IN_DEV_CONF_GET(in_dev, NOPOLICY))
		rth->u.dst.flags |= DST_NOPOLICY;
	rth->fl.fl4_dst	= daddr;
	rth->rt_dst	= daddr;
	rth->fl.fl4_tos	= tos;
	rth->fl.mark    = skb->mark;
	rth->fl.fl4_src	= saddr;
	rth->rt_src	= saddr;
#ifdef CONFIG_NET_CLS_ROUTE
	rth->u.dst.tclassid = itag;
#endif
	rth->rt_iif	=
	rth->fl.iif	= dev->ifindex;
	rth->u.dst.dev	= init_net.loopback_dev;
	dev_hold(rth->u.dst.dev);
	rth->idev	= in_dev_get(rth->u.dst.dev);
	rth->fl.oif	= 0;
	rth->rt_gateway	= daddr;
	rth->rt_spec_dst= spec_dst;
	rth->rt_genid	= rt_genid(dev_net(dev));
	rth->rt_flags	= RTCF_MULTICAST;
	rth->rt_type	= RTN_MULTICAST;
	if (our) {
		rth->u.dst.input= ip_local_deliver;
		rth->rt_flags |= RTCF_LOCAL;
	}

#ifdef CONFIG_IP_MROUTE
	if (!ipv4_is_local_multicast(daddr) && IN_DEV_MFORWARD(in_dev))
		rth->u.dst.input = ip_mr_input;
#endif
	RT_CACHE_STAT_INC(in_slow_mc);

	in_dev_put(in_dev);
	hash = rt_hash(daddr, saddr, dev->ifindex, rt_genid(dev_net(dev)));
	return rt_intern_hash(hash, rth, NULL, skb);

e_nobufs:
	in_dev_put(in_dev);
	return -ENOBUFS;

e_inval:
	in_dev_put(in_dev);
	return -EINVAL;
}