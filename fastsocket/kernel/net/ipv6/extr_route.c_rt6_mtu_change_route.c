#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rt6_mtu_change_arg {scalar_t__ dev; scalar_t__ mtu; } ;
struct TYPE_7__ {scalar_t__* metrics; } ;
struct TYPE_6__ {TYPE_3__ dst; } ;
struct rt6_info {scalar_t__ rt6i_dev; TYPE_2__ u; } ;
struct net {int dummy; } ;
struct TYPE_5__ {scalar_t__ mtu6; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 int RTAX_ADVMSS ; 
 int RTAX_MTU ; 
 struct inet6_dev* __in6_dev_get (scalar_t__) ; 
 struct net* dev_net (scalar_t__) ; 
 int /*<<< orphan*/  dst_metric_locked (TYPE_3__*,int) ; 
 scalar_t__ dst_mtu (TYPE_3__*) ; 
 scalar_t__ ipv6_advmss (struct net*,scalar_t__) ; 

__attribute__((used)) static int rt6_mtu_change_route(struct rt6_info *rt, void *p_arg)
{
	struct rt6_mtu_change_arg *arg = (struct rt6_mtu_change_arg *) p_arg;
	struct inet6_dev *idev;
	struct net *net = dev_net(arg->dev);

	/* In IPv6 pmtu discovery is not optional,
	   so that RTAX_MTU lock cannot disable it.
	   We still use this lock to block changes
	   caused by addrconf/ndisc.
	*/

	idev = __in6_dev_get(arg->dev);
	if (idev == NULL)
		return 0;

	/* For administrative MTU increase, there is no way to discover
	   IPv6 PMTU increase, so PMTU increase should be updated here.
	   Since RFC 1981 doesn't include administrative MTU increase
	   update PMTU increase is a MUST. (i.e. jumbo frame)
	 */
	/*
	   If new MTU is less than route PMTU, this new MTU will be the
	   lowest MTU in the path, update the route PMTU to reflect PMTU
	   decreases; if new MTU is greater than route PMTU, and the
	   old MTU is the lowest MTU in the path, update the route PMTU
	   to reflect the increase. In this case if the other nodes' MTU
	   also have the lowest MTU, TOO BIG MESSAGE will be lead to
	   PMTU discouvery.
	 */
	if (rt->rt6i_dev == arg->dev &&
	    !dst_metric_locked(&rt->u.dst, RTAX_MTU) &&
	    (dst_mtu(&rt->u.dst) >= arg->mtu ||
	     (dst_mtu(&rt->u.dst) < arg->mtu &&
	      dst_mtu(&rt->u.dst) == idev->cnf.mtu6))) {
		rt->u.dst.metrics[RTAX_MTU-1] = arg->mtu;
		rt->u.dst.metrics[RTAX_ADVMSS-1] = ipv6_advmss(net, arg->mtu);
	}
	return 0;
}