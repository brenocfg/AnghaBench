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
struct net_device {int tx_queue_len; int flags; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  mtu; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * wireless_handlers; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIRO_DEF_MTU ; 
 int /*<<< orphan*/  ARPHRD_IEEE80211 ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  airo11_netdev_ops ; 
 int /*<<< orphan*/  airo_handler_def ; 
 int /*<<< orphan*/  airo_header_ops ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wifi_setup(struct net_device *dev)
{
	dev->netdev_ops = &airo11_netdev_ops;
	dev->header_ops = &airo_header_ops;
	dev->wireless_handlers = &airo_handler_def;

	dev->type               = ARPHRD_IEEE80211;
	dev->hard_header_len    = ETH_HLEN;
	dev->mtu                = AIRO_DEF_MTU;
	dev->addr_len           = ETH_ALEN;
	dev->tx_queue_len       = 100; 

	memset(dev->broadcast,0xFF, ETH_ALEN);

	dev->flags              = IFF_BROADCAST|IFF_MULTICAST;
}