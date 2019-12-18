#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {unsigned int mtu; } ;
struct neighbour {int dummy; } ;
struct TYPE_6__ {unsigned int* metrics; struct net_device* dev; struct neighbour* neighbour; } ;
struct TYPE_5__ {TYPE_2__ dst; } ;
struct dn_route {TYPE_1__ u; scalar_t__ rt_gateway; int /*<<< orphan*/  rt_type; } ;
struct dn_fib_res {int /*<<< orphan*/  type; struct dn_fib_info* fi; } ;
struct dn_fib_info {int /*<<< orphan*/  fib_metrics; } ;
struct TYPE_7__ {scalar_t__ nh_scope; } ;

/* Variables and functions */
 scalar_t__ DN_FIB_RES_GW (struct dn_fib_res) ; 
 TYPE_4__ DN_FIB_RES_NH (struct dn_fib_res) ; 
 scalar_t__ IS_ERR (struct neighbour*) ; 
 int PTR_ERR (struct neighbour*) ; 
 int RTAX_ADVMSS ; 
 int RTAX_MTU ; 
 scalar_t__ RT_SCOPE_LINK ; 
 struct neighbour* __neigh_lookup_errno (int /*<<< orphan*/ *,scalar_t__*,struct net_device*) ; 
 unsigned int dn_mss_from_pmtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_neigh_table ; 
 unsigned int dst_metric (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dst_mtu (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dn_rt_set_next_hop(struct dn_route *rt, struct dn_fib_res *res)
{
	struct dn_fib_info *fi = res->fi;
	struct net_device *dev = rt->u.dst.dev;
	struct neighbour *n;
	unsigned mss;

	if (fi) {
		if (DN_FIB_RES_GW(*res) &&
		    DN_FIB_RES_NH(*res).nh_scope == RT_SCOPE_LINK)
			rt->rt_gateway = DN_FIB_RES_GW(*res);
		memcpy(rt->u.dst.metrics, fi->fib_metrics,
		       sizeof(rt->u.dst.metrics));
	}
	rt->rt_type = res->type;

	if (dev != NULL && rt->u.dst.neighbour == NULL) {
		n = __neigh_lookup_errno(&dn_neigh_table, &rt->rt_gateway, dev);
		if (IS_ERR(n))
			return PTR_ERR(n);
		rt->u.dst.neighbour = n;
	}

	if (dst_metric(&rt->u.dst, RTAX_MTU) == 0 ||
	    dst_metric(&rt->u.dst, RTAX_MTU) > rt->u.dst.dev->mtu)
		rt->u.dst.metrics[RTAX_MTU-1] = rt->u.dst.dev->mtu;
	mss = dn_mss_from_pmtu(dev, dst_mtu(&rt->u.dst));
	if (dst_metric(&rt->u.dst, RTAX_ADVMSS) == 0 ||
	    dst_metric(&rt->u.dst, RTAX_ADVMSS) > mss)
		rt->u.dst.metrics[RTAX_ADVMSS-1] = mss;
	return 0;
}