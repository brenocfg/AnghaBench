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
struct pasemi_mac {int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int tx_max_pending; int tx_pending; int rx_max_pending; int rx_pending; } ;

/* Variables and functions */
 int RING_USED (int /*<<< orphan*/ ) ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 struct pasemi_mac* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
pasemi_mac_ethtool_get_ringparam(struct net_device *netdev,
				 struct ethtool_ringparam *ering)
{
	struct pasemi_mac *mac = netdev_priv(netdev);

	ering->tx_max_pending = TX_RING_SIZE/2;
	ering->tx_pending = RING_USED(mac->tx)/2;
	ering->rx_max_pending = RX_RING_SIZE/4;
	ering->rx_pending = RING_USED(mac->rx)/4;
}