#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rt6_info {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nl_net; int /*<<< orphan*/ * nlh; int /*<<< orphan*/  pid; } ;
struct fib6_config {int fc_flags; int /*<<< orphan*/  fc_gateway; TYPE_1__ fc_nlinfo; int /*<<< orphan*/  fc_ifindex; int /*<<< orphan*/  fc_metric; int /*<<< orphan*/  fc_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6_RT_PRIO_USER ; 
 int /*<<< orphan*/  RT6_TABLE_DFLT ; 
 int RTF_ADDRCONF ; 
 int RTF_DEFAULT ; 
 int RTF_EXPIRES ; 
 int RTF_GATEWAY ; 
 int RTF_PREF (unsigned int) ; 
 int RTF_UP ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  ip6_route_add (struct fib6_config*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,struct in6_addr*) ; 
 struct rt6_info* rt6_get_dflt_router (struct in6_addr*,struct net_device*) ; 

struct rt6_info *rt6_add_dflt_router(struct in6_addr *gwaddr,
				     struct net_device *dev,
				     unsigned int pref)
{
	struct fib6_config cfg = {
		.fc_table	= RT6_TABLE_DFLT,
		.fc_metric	= IP6_RT_PRIO_USER,
		.fc_ifindex	= dev->ifindex,
		.fc_flags	= RTF_GATEWAY | RTF_ADDRCONF | RTF_DEFAULT |
				  RTF_UP | RTF_EXPIRES | RTF_PREF(pref),
		.fc_nlinfo.pid = 0,
		.fc_nlinfo.nlh = NULL,
		.fc_nlinfo.nl_net = dev_net(dev),
	};

	ipv6_addr_copy(&cfg.fc_gateway, gwaddr);

	ip6_route_add(&cfg);

	return rt6_get_dflt_router(gwaddr, dev);
}