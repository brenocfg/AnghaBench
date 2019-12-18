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
typedef  int u32 ;
struct net_device {scalar_t__ type; int flags; int /*<<< orphan*/  ifindex; } ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nl_net; } ;
struct fib6_config {unsigned long fc_expires; int fc_dst_len; int fc_flags; int /*<<< orphan*/  fc_dst; int /*<<< orphan*/  fc_protocol; TYPE_1__ fc_nlinfo; int /*<<< orphan*/  fc_ifindex; int /*<<< orphan*/  fc_metric; int /*<<< orphan*/  fc_table; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_SIT ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IP6_RT_PRIO_ADDRCONF ; 
 int /*<<< orphan*/  RT6_TABLE_PREFIX ; 
 int RTF_NONEXTHOP ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RTPROT_KERNEL ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  ip6_route_add (struct fib6_config*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,struct in6_addr*) ; 

__attribute__((used)) static void
addrconf_prefix_route(struct in6_addr *pfx, int plen, struct net_device *dev,
		      unsigned long expires, u32 flags)
{
	struct fib6_config cfg = {
		.fc_table = RT6_TABLE_PREFIX,
		.fc_metric = IP6_RT_PRIO_ADDRCONF,
		.fc_ifindex = dev->ifindex,
		.fc_expires = expires,
		.fc_dst_len = plen,
		.fc_flags = RTF_UP | flags,
		.fc_nlinfo.nl_net = dev_net(dev),
		.fc_protocol = RTPROT_KERNEL,
	};

	ipv6_addr_copy(&cfg.fc_dst, pfx);

	/* Prevent useless cloning on PtP SIT.
	   This thing is done here expecting that the whole
	   class of non-broadcast devices need not cloning.
	 */
#if defined(CONFIG_IPV6_SIT) || defined(CONFIG_IPV6_SIT_MODULE)
	if (dev->type == ARPHRD_SIT && (dev->flags & IFF_POINTOPOINT))
		cfg.fc_flags |= RTF_NONEXTHOP;
#endif

	ip6_route_add(&cfg);
}