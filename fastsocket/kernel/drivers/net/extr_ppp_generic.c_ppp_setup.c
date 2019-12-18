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
struct net_device {int tx_queue_len; int flags; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  features; int /*<<< orphan*/  type; scalar_t__ addr_len; int /*<<< orphan*/  mtu; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_PPP ; 
 int IFF_MULTICAST ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IFF_XMIT_DST_RELEASE ; 
 int /*<<< orphan*/  NETIF_F_NETNS_LOCAL ; 
 int /*<<< orphan*/  PPP_HDRLEN ; 
 int /*<<< orphan*/  PPP_MTU ; 
 int /*<<< orphan*/  ppp_netdev_ops ; 

__attribute__((used)) static void ppp_setup(struct net_device *dev)
{
	dev->netdev_ops = &ppp_netdev_ops;
	dev->hard_header_len = PPP_HDRLEN;
	dev->mtu = PPP_MTU;
	dev->addr_len = 0;
	dev->tx_queue_len = 3;
	dev->type = ARPHRD_PPP;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
	dev->features |= NETIF_F_NETNS_LOCAL;
	dev->priv_flags &= ~IFF_XMIT_DST_RELEASE;
}