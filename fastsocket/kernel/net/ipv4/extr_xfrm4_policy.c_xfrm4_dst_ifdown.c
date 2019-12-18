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
struct TYPE_6__ {scalar_t__ child; scalar_t__ xfrm; } ;
struct TYPE_5__ {struct in_device* idev; } ;
struct TYPE_7__ {TYPE_2__ dst; TYPE_1__ rt; } ;
struct xfrm_dst {TYPE_3__ u; } ;
struct net_device {int dummy; } ;
struct in_device {struct net_device* dev; } ;
struct dst_entry {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  loopback_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __in_dev_put (struct in_device*) ; 
 TYPE_4__* dev_net (struct net_device*) ; 
 struct in_device* in_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_dev_hold (struct in_device*) ; 
 int /*<<< orphan*/  in_dev_put (struct in_device*) ; 
 int /*<<< orphan*/  xfrm_dst_ifdown (struct dst_entry*,struct net_device*) ; 

__attribute__((used)) static void xfrm4_dst_ifdown(struct dst_entry *dst, struct net_device *dev,
			     int unregister)
{
	struct xfrm_dst *xdst;

	if (!unregister)
		return;

	xdst = (struct xfrm_dst *)dst;
	if (xdst->u.rt.idev->dev == dev) {
		struct in_device *loopback_idev =
			in_dev_get(dev_net(dev)->loopback_dev);
		BUG_ON(!loopback_idev);

		do {
			in_dev_put(xdst->u.rt.idev);
			xdst->u.rt.idev = loopback_idev;
			in_dev_hold(loopback_idev);
			xdst = (struct xfrm_dst *)xdst->u.dst.child;
		} while (xdst->u.dst.xfrm);

		__in_dev_put(loopback_idev);
	}

	xfrm_dst_ifdown(dst, dev);
}