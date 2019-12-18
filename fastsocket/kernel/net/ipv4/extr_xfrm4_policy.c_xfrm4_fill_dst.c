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
struct flowi {int dummy; } ;
struct TYPE_7__ {int rt_flags; int /*<<< orphan*/  rt_spec_dst; int /*<<< orphan*/  rt_gateway; int /*<<< orphan*/  rt_dst; int /*<<< orphan*/  rt_src; int /*<<< orphan*/  rt_type; TYPE_2__* peer; int /*<<< orphan*/  idev; struct flowi fl; } ;
struct TYPE_5__ {struct net_device* dev; } ;
struct TYPE_8__ {TYPE_3__ rt; TYPE_1__ dst; } ;
struct xfrm_dst {TYPE_4__ u; scalar_t__ route; } ;
struct rtable {int rt_flags; int /*<<< orphan*/  rt_spec_dst; int /*<<< orphan*/  rt_gateway; int /*<<< orphan*/  rt_dst; int /*<<< orphan*/  rt_src; int /*<<< orphan*/  rt_type; TYPE_2__* peer; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int ENODEV ; 
 int RTCF_BROADCAST ; 
 int RTCF_LOCAL ; 
 int RTCF_MULTICAST ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  in_dev_get (struct net_device*) ; 

__attribute__((used)) static int xfrm4_fill_dst(struct xfrm_dst *xdst, struct net_device *dev,
			  struct flowi *fl)
{
	struct rtable *rt = (struct rtable *)xdst->route;

	xdst->u.rt.fl = *fl;

	xdst->u.dst.dev = dev;
	dev_hold(dev);

	xdst->u.rt.idev = in_dev_get(dev);
	if (!xdst->u.rt.idev)
		return -ENODEV;

	xdst->u.rt.peer = rt->peer;
	if (rt->peer)
		atomic_inc(&rt->peer->refcnt);

	/* Sheit... I remember I did this right. Apparently,
	 * it was magically lost, so this code needs audit */
	xdst->u.rt.rt_flags = rt->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST |
					      RTCF_LOCAL);
	xdst->u.rt.rt_type = rt->rt_type;
	xdst->u.rt.rt_src = rt->rt_src;
	xdst->u.rt.rt_dst = rt->rt_dst;
	xdst->u.rt.rt_gateway = rt->rt_gateway;
	xdst->u.rt.rt_spec_dst = rt->rt_spec_dst;

	return 0;
}