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
struct net_device {int flags; int tx_queue_len; int /*<<< orphan*/  type; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  features; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * header_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE1394 ; 
 int /*<<< orphan*/  ETH1394_ALEN ; 
 int /*<<< orphan*/  ETH1394_HLEN ; 
 int /*<<< orphan*/  ETHER1394_TIMEOUT ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  NETIF_F_HIGHDMA ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether1394_header_ops ; 
 int /*<<< orphan*/  ether1394_netdev_ops ; 
 int /*<<< orphan*/  ethtool_ops ; 

__attribute__((used)) static void ether1394_init_dev(struct net_device *dev)
{

	dev->header_ops		= &ether1394_header_ops;
	dev->netdev_ops		= &ether1394_netdev_ops;

	SET_ETHTOOL_OPS(dev, &ethtool_ops);

	dev->watchdog_timeo	= ETHER1394_TIMEOUT;
	dev->flags		= IFF_BROADCAST | IFF_MULTICAST;
	dev->features		= NETIF_F_HIGHDMA;
	dev->addr_len		= ETH1394_ALEN;
	dev->hard_header_len 	= ETH1394_HLEN;
	dev->type		= ARPHRD_IEEE1394;

	/* FIXME: This value was copied from ether_setup(). Is it too much? */
	dev->tx_queue_len	= 1000;
}