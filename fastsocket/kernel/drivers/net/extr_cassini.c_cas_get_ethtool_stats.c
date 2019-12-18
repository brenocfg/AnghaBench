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
typedef  int /*<<< orphan*/  u64 ;
struct net_device_stats {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  collisions; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct cas {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CAS_NUM_STAT_KEYS ; 
 struct net_device_stats* cas_get_stats (int /*<<< orphan*/ ) ; 
 struct cas* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void cas_get_ethtool_stats(struct net_device *dev,
				      struct ethtool_stats *estats, u64 *data)
{
	struct cas *cp = netdev_priv(dev);
	struct net_device_stats *stats = cas_get_stats(cp->dev);
	int i = 0;
	data[i++] = stats->collisions;
	data[i++] = stats->rx_bytes;
	data[i++] = stats->rx_crc_errors;
	data[i++] = stats->rx_dropped;
	data[i++] = stats->rx_errors;
	data[i++] = stats->rx_fifo_errors;
	data[i++] = stats->rx_frame_errors;
	data[i++] = stats->rx_length_errors;
	data[i++] = stats->rx_over_errors;
	data[i++] = stats->rx_packets;
	data[i++] = stats->tx_aborted_errors;
	data[i++] = stats->tx_bytes;
	data[i++] = stats->tx_dropped;
	data[i++] = stats->tx_errors;
	data[i++] = stats->tx_fifo_errors;
	data[i++] = stats->tx_packets;
	BUG_ON(i != CAS_NUM_STAT_KEYS);
}