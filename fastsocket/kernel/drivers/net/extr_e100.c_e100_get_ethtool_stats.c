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
typedef  unsigned long u64 ;
struct nic {unsigned long tx_deferred; unsigned long tx_single_collisions; unsigned long tx_multiple_collisions; unsigned long tx_fc_pause; unsigned long rx_fc_pause; unsigned long rx_fc_unsupported; unsigned long tx_tco_frames; unsigned long rx_tco_frames; } ;
struct net_device {int /*<<< orphan*/  stats; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int E100_NET_STATS_LEN ; 
 struct nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void e100_get_ethtool_stats(struct net_device *netdev,
	struct ethtool_stats *stats, u64 *data)
{
	struct nic *nic = netdev_priv(netdev);
	int i;

	for (i = 0; i < E100_NET_STATS_LEN; i++)
		data[i] = ((unsigned long *)&netdev->stats)[i];

	data[i++] = nic->tx_deferred;
	data[i++] = nic->tx_single_collisions;
	data[i++] = nic->tx_multiple_collisions;
	data[i++] = nic->tx_fc_pause;
	data[i++] = nic->rx_fc_pause;
	data[i++] = nic->rx_fc_unsupported;
	data[i++] = nic->tx_tco_frames;
	data[i++] = nic->rx_tco_frames;
}