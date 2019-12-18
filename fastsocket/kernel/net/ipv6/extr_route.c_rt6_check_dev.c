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
struct rt6_info {TYPE_2__* rt6i_idev; struct net_device* rt6i_dev; } ;
struct net_device {int ifindex; int flags; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int ifindex; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 

__attribute__((used)) static inline int rt6_check_dev(struct rt6_info *rt, int oif)
{
	struct net_device *dev = rt->rt6i_dev;
	if (!oif || dev->ifindex == oif)
		return 2;
	if ((dev->flags & IFF_LOOPBACK) &&
	    rt->rt6i_idev && rt->rt6i_idev->dev->ifindex == oif)
		return 1;
	return 0;
}