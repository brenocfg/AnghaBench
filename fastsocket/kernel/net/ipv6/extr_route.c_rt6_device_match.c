#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct rt6_info* rt6_next; } ;
struct TYPE_7__ {TYPE_1__ dst; } ;
struct rt6_info {TYPE_4__* rt6i_idev; struct net_device* rt6i_dev; TYPE_2__ u; } ;
struct net_device {int ifindex; int flags; } ;
struct TYPE_10__ {struct rt6_info* ip6_null_entry; } ;
struct net {TYPE_5__ ipv6; } ;
struct in6_addr {int dummy; } ;
struct TYPE_9__ {TYPE_3__* dev; } ;
struct TYPE_8__ {int ifindex; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int RT6_LOOKUP_F_IFACE ; 
 scalar_t__ ipv6_addr_any (struct in6_addr*) ; 
 scalar_t__ ipv6_chk_addr (struct net*,struct in6_addr*,struct net_device*,int) ; 

__attribute__((used)) static inline struct rt6_info *rt6_device_match(struct net *net,
						    struct rt6_info *rt,
						    struct in6_addr *saddr,
						    int oif,
						    int flags)
{
	struct rt6_info *local = NULL;
	struct rt6_info *sprt;

	if (!oif && ipv6_addr_any(saddr))
		goto out;

	for (sprt = rt; sprt; sprt = sprt->u.dst.rt6_next) {
		struct net_device *dev = sprt->rt6i_dev;

		if (oif) {
			if (dev->ifindex == oif)
				return sprt;
			if (dev->flags & IFF_LOOPBACK) {
				if (sprt->rt6i_idev == NULL ||
				    sprt->rt6i_idev->dev->ifindex != oif) {
					if (flags & RT6_LOOKUP_F_IFACE && oif)
						continue;
					if (local && (!oif ||
						      local->rt6i_idev->dev->ifindex == oif))
						continue;
				}
				local = sprt;
			}
		} else {
			if (ipv6_chk_addr(net, saddr, dev,
					  flags & RT6_LOOKUP_F_IFACE))
				return sprt;
		}
	}

	if (oif) {
		if (local)
			return local;

		if (flags & RT6_LOOKUP_F_IFACE)
			return net->ipv6.ip6_null_entry;
	}
out:
	return rt;
}