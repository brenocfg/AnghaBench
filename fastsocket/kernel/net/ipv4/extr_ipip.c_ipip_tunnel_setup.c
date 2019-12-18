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
struct net_device {int addr_len; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  features; scalar_t__ iflink; int /*<<< orphan*/  flags; scalar_t__ mtu; scalar_t__ hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/  destructor; int /*<<< orphan*/ * netdev_ops; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_TUNNEL ; 
 scalar_t__ ETH_DATA_LEN ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IFF_XMIT_DST_RELEASE ; 
 scalar_t__ LL_MAX_HEADER ; 
 int /*<<< orphan*/  NETIF_F_NETNS_LOCAL ; 
 int /*<<< orphan*/  free_netdev ; 
 int /*<<< orphan*/  ipip_netdev_ops ; 

__attribute__((used)) static void ipip_tunnel_setup(struct net_device *dev)
{
	dev->netdev_ops		= &ipip_netdev_ops;
	dev->destructor		= free_netdev;

	dev->type		= ARPHRD_TUNNEL;
	dev->hard_header_len 	= LL_MAX_HEADER + sizeof(struct iphdr);
	dev->mtu		= ETH_DATA_LEN - sizeof(struct iphdr);
	dev->flags		= IFF_NOARP;
	dev->iflink		= 0;
	dev->addr_len		= 4;
	dev->features		|= NETIF_F_NETNS_LOCAL;
	dev->priv_flags		&= ~IFF_XMIT_DST_RELEASE;
}