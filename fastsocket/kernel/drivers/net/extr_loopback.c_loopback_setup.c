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
struct net_device {int mtu; int features; int /*<<< orphan*/  destructor; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; scalar_t__ tx_queue_len; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  hard_header_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_LOOPBACK ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  IFF_LOOPBACK ; 
 int /*<<< orphan*/  IFF_XMIT_DST_RELEASE ; 
 int NETIF_F_FRAGLIST ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_NETNS_LOCAL ; 
 int NETIF_F_NO_CSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  eth_header_ops ; 
 int /*<<< orphan*/  loopback_dev_free ; 
 int /*<<< orphan*/  loopback_ethtool_ops ; 
 int /*<<< orphan*/  loopback_ops ; 

__attribute__((used)) static void loopback_setup(struct net_device *dev)
{
	dev->mtu		= (16 * 1024) + 20 + 20 + 12;
	dev->hard_header_len	= ETH_HLEN;	/* 14	*/
	dev->addr_len		= ETH_ALEN;	/* 6	*/
	dev->tx_queue_len	= 0;
	dev->type		= ARPHRD_LOOPBACK;	/* 0x0001*/
	dev->flags		= IFF_LOOPBACK;
	dev->priv_flags	       &= ~IFF_XMIT_DST_RELEASE;
	dev->features 		= NETIF_F_SG | NETIF_F_FRAGLIST
		| NETIF_F_TSO
		| NETIF_F_NO_CSUM
		| NETIF_F_HIGHDMA
		| NETIF_F_LLTX
		| NETIF_F_NETNS_LOCAL
		| NETIF_F_VLAN_CHALLENGED;
	dev->ethtool_ops	= &loopback_ethtool_ops;
	dev->header_ops		= &eth_header_ops;
	dev->netdev_ops		= &loopback_ops;
	dev->destructor		= loopback_dev_free;
}