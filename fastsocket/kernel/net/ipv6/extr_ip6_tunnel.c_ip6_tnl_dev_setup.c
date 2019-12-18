#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int addr_len; int /*<<< orphan*/  features; int /*<<< orphan*/  flags; scalar_t__ mtu; scalar_t__ hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/  destructor; int /*<<< orphan*/ * netdev_ops; } ;
struct ipv6hdr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_TUNNEL6 ; 
 scalar_t__ ETH_DATA_LEN ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 scalar_t__ LL_MAX_HEADER ; 
 int /*<<< orphan*/  NETIF_F_NETNS_LOCAL ; 
 int /*<<< orphan*/  free_netdev ; 
 int /*<<< orphan*/  ip6_tnl_netdev_ops ; 

__attribute__((used)) static void ip6_tnl_dev_setup(struct net_device *dev)
{
	dev->netdev_ops = &ip6_tnl_netdev_ops;
	dev->destructor = free_netdev;

	dev->type = ARPHRD_TUNNEL6;
	dev->hard_header_len = LL_MAX_HEADER + sizeof (struct ipv6hdr);
	dev->mtu = ETH_DATA_LEN - sizeof (struct ipv6hdr);
	dev->flags |= IFF_NOARP;
	dev->addr_len = sizeof(struct in6_addr);
	dev->features |= NETIF_F_NETNS_LOCAL;
}