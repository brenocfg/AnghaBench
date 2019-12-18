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
struct net_device {int flags; int tx_queue_len; int /*<<< orphan*/  destructor; int /*<<< orphan*/ * netdev_ops; scalar_t__ addr_len; scalar_t__ hard_header_len; int /*<<< orphan*/  mtu; int /*<<< orphan*/  type; int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_PHONET_PIPE ; 
 int /*<<< orphan*/  GPRS_DEFAULT_MTU ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  NETIF_F_FRAGLIST ; 
 int /*<<< orphan*/  free_netdev ; 
 int /*<<< orphan*/  gprs_netdev_ops ; 

__attribute__((used)) static void gprs_setup(struct net_device *dev)
{
	dev->features		= NETIF_F_FRAGLIST;
	dev->type		= ARPHRD_PHONET_PIPE;
	dev->flags		= IFF_POINTOPOINT | IFF_NOARP;
	dev->mtu		= GPRS_DEFAULT_MTU;
	dev->hard_header_len	= 0;
	dev->addr_len		= 0;
	dev->tx_queue_len	= 10;

	dev->netdev_ops		= &gprs_netdev_ops;
	dev->destructor		= free_netdev;
}