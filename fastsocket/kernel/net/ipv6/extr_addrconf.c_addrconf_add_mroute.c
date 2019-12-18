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
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_2__ {int /*<<< orphan*/  nl_net; } ;
struct fib6_config {int fc_dst_len; int /*<<< orphan*/  fc_dst; TYPE_1__ fc_nlinfo; int /*<<< orphan*/  fc_flags; int /*<<< orphan*/  fc_ifindex; int /*<<< orphan*/  fc_metric; int /*<<< orphan*/  fc_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6_RT_PRIO_ADDRCONF ; 
 int /*<<< orphan*/  RT6_TABLE_LOCAL ; 
 int /*<<< orphan*/  RTF_UP ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  ip6_route_add (struct fib6_config*) ; 
 int /*<<< orphan*/  ipv6_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void addrconf_add_mroute(struct net_device *dev)
{
	struct fib6_config cfg = {
		.fc_table = RT6_TABLE_LOCAL,
		.fc_metric = IP6_RT_PRIO_ADDRCONF,
		.fc_ifindex = dev->ifindex,
		.fc_dst_len = 8,
		.fc_flags = RTF_UP,
		.fc_nlinfo.nl_net = dev_net(dev),
	};

	ipv6_addr_set(&cfg.fc_dst, htonl(0xFF000000), 0, 0, 0);

	ip6_route_add(&cfg);
}