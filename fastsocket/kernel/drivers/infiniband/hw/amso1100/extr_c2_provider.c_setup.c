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
struct net_device {int mtu; int /*<<< orphan*/  flags; scalar_t__ tx_queue_len; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  type; scalar_t__ watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  c2_pseudo_netdev_ops ; 

__attribute__((used)) static void setup(struct net_device *netdev)
{
	netdev->netdev_ops = &c2_pseudo_netdev_ops;

	netdev->watchdog_timeo = 0;
	netdev->type = ARPHRD_ETHER;
	netdev->mtu = 1500;
	netdev->hard_header_len = ETH_HLEN;
	netdev->addr_len = ETH_ALEN;
	netdev->tx_queue_len = 0;
	netdev->flags |= IFF_NOARP;
}