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
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int autoneg; int rx_pause; int tx_pause; } ;
struct b44 {int flags; } ;

/* Variables and functions */
 int B44_FLAG_PAUSE_AUTO ; 
 int B44_FLAG_RX_PAUSE ; 
 int B44_FLAG_TX_PAUSE ; 
 struct b44* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void b44_get_pauseparam(struct net_device *dev,
				struct ethtool_pauseparam *epause)
{
	struct b44 *bp = netdev_priv(dev);

	epause->autoneg =
		(bp->flags & B44_FLAG_PAUSE_AUTO) != 0;
	epause->rx_pause =
		(bp->flags & B44_FLAG_RX_PAUSE) != 0;
	epause->tx_pause =
		(bp->flags & B44_FLAG_TX_PAUSE) != 0;
}