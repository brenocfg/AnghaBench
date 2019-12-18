#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct net_device {int flags; } ;
struct TYPE_11__ {TYPE_9__* ip6_blk_hole_entry; TYPE_6__* ip6_prohibit_entry; TYPE_3__* ip6_null_entry; } ;
struct net {TYPE_10__ ipv6; } ;
struct TYPE_18__ {struct net_device* dev; } ;
struct TYPE_19__ {TYPE_7__ dst; } ;
struct TYPE_20__ {void* rt6i_idev; TYPE_8__ u; } ;
struct TYPE_15__ {struct net_device* dev; } ;
struct TYPE_16__ {TYPE_4__ dst; } ;
struct TYPE_17__ {void* rt6i_idev; TYPE_5__ u; } ;
struct TYPE_12__ {struct net_device* dev; } ;
struct TYPE_13__ {TYPE_1__ dst; } ;
struct TYPE_14__ {void* rt6i_idev; TYPE_2__ u; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 unsigned long NETDEV_REGISTER ; 
 int NOTIFY_OK ; 
 struct net* dev_net (struct net_device*) ; 
 void* in6_dev_get (struct net_device*) ; 

__attribute__((used)) static int ip6_route_dev_notify(struct notifier_block *this,
				unsigned long event, void *data)
{
	struct net_device *dev = (struct net_device *)data;
	struct net *net = dev_net(dev);

	if (event == NETDEV_REGISTER && (dev->flags & IFF_LOOPBACK)) {
		net->ipv6.ip6_null_entry->u.dst.dev = dev;
		net->ipv6.ip6_null_entry->rt6i_idev = in6_dev_get(dev);
#ifdef CONFIG_IPV6_MULTIPLE_TABLES
		net->ipv6.ip6_prohibit_entry->u.dst.dev = dev;
		net->ipv6.ip6_prohibit_entry->rt6i_idev = in6_dev_get(dev);
		net->ipv6.ip6_blk_hole_entry->u.dst.dev = dev;
		net->ipv6.ip6_blk_hole_entry->rt6i_idev = in6_dev_get(dev);
#endif
	}

	return NOTIFY_OK;
}