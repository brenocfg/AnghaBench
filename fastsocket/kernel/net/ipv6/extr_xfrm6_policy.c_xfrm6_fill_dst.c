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
struct TYPE_7__ {int rt6i_flags; int /*<<< orphan*/  rt6i_src; int /*<<< orphan*/  rt6i_dst; int /*<<< orphan*/  rt6i_gateway; TYPE_2__* rt6i_node; int /*<<< orphan*/  rt6i_metric; int /*<<< orphan*/  rt6i_idev; } ;
struct TYPE_5__ {struct net_device* dev; } ;
struct TYPE_8__ {TYPE_3__ rt6; TYPE_1__ dst; } ;
struct xfrm_dst {TYPE_4__ u; int /*<<< orphan*/  route_cookie; scalar_t__ route; } ;
struct rt6_info {int rt6i_flags; int /*<<< orphan*/  rt6i_src; int /*<<< orphan*/  rt6i_dst; int /*<<< orphan*/  rt6i_gateway; TYPE_2__* rt6i_node; int /*<<< orphan*/  rt6i_metric; } ;
struct net_device {int dummy; } ;
struct flowi {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  fn_sernum; } ;

/* Variables and functions */
 int ENODEV ; 
 int RTF_ANYCAST ; 
 int RTF_LOCAL ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_get (struct net_device*) ; 

__attribute__((used)) static int xfrm6_fill_dst(struct xfrm_dst *xdst, struct net_device *dev,
			  struct flowi *fl)
{
	struct rt6_info *rt = (struct rt6_info*)xdst->route;

	xdst->u.dst.dev = dev;
	dev_hold(dev);

	xdst->u.rt6.rt6i_idev = in6_dev_get(dev);
	if (!xdst->u.rt6.rt6i_idev)
		return -ENODEV;

	/* Sheit... I remember I did this right. Apparently,
	 * it was magically lost, so this code needs audit */
	xdst->u.rt6.rt6i_flags = rt->rt6i_flags & (RTF_ANYCAST |
						   RTF_LOCAL);
	xdst->u.rt6.rt6i_metric = rt->rt6i_metric;
	xdst->u.rt6.rt6i_node = rt->rt6i_node;
	if (rt->rt6i_node)
		xdst->route_cookie = rt->rt6i_node->fn_sernum;
	xdst->u.rt6.rt6i_gateway = rt->rt6i_gateway;
	xdst->u.rt6.rt6i_dst = rt->rt6i_dst;
	xdst->u.rt6.rt6i_src = rt->rt6i_src;

	return 0;
}