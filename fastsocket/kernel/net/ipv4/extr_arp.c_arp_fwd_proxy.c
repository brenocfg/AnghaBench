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
struct TYPE_4__ {struct net_device* dev; } ;
struct TYPE_3__ {TYPE_2__ dst; } ;
struct rtable {TYPE_1__ u; } ;
struct net_device {int dummy; } ;
struct in_device {int dummy; } ;

/* Variables and functions */
 int IN_DEV_MEDIUM_ID (struct in_device*) ; 
 int /*<<< orphan*/  IN_DEV_PROXY_ARP (struct in_device*) ; 
 struct in_device* in_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in_dev_put (struct in_device*) ; 

__attribute__((used)) static inline int arp_fwd_proxy(struct in_device *in_dev,
				struct net_device *dev,	struct rtable *rt)
{
	struct in_device *out_dev;
	int imi, omi = -1;

	if (rt->u.dst.dev == dev)
		return 0;

	if (!IN_DEV_PROXY_ARP(in_dev))
		return 0;

	if ((imi = IN_DEV_MEDIUM_ID(in_dev)) == 0)
		return 1;
	if (imi == -1)
		return 0;

	/* place to check for proxy_arp for routes */

	if ((out_dev = in_dev_get(rt->u.dst.dev)) != NULL) {
		omi = IN_DEV_MEDIUM_ID(out_dev);
		in_dev_put(out_dev);
	}
	return (omi != imi && omi != -1);
}