#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device_stats {scalar_t__ tx_window_errors; scalar_t__ tx_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_length_errors; scalar_t__ rx_errors; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
struct efx_mac_stats {scalar_t__ tx_bad; scalar_t__ rx_symbol_error; scalar_t__ tx_late_collision; int /*<<< orphan*/  rx_missed; int /*<<< orphan*/  rx_overflow; scalar_t__ rx_align_error; scalar_t__ rx_bad; scalar_t__ rx_length_error; scalar_t__ rx_gtjumbo; int /*<<< orphan*/  tx_collision; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct efx_nic {int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  n_rx_nodesc_drop_cnt; TYPE_1__* type; struct efx_mac_stats mac_stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_stats ) (struct efx_nic*) ;} ;

/* Variables and functions */
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 

__attribute__((used)) static struct net_device_stats *efx_net_stats(struct net_device *net_dev)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	struct efx_mac_stats *mac_stats = &efx->mac_stats;
	struct net_device_stats *stats = &net_dev->stats;

	spin_lock_bh(&efx->stats_lock);

	efx->type->update_stats(efx);

	stats->rx_packets = mac_stats->rx_packets;
	stats->tx_packets = mac_stats->tx_packets;
	stats->rx_bytes = mac_stats->rx_bytes;
	stats->tx_bytes = mac_stats->tx_bytes;
	stats->rx_dropped = efx->n_rx_nodesc_drop_cnt;
	stats->multicast = mac_stats->rx_multicast;
	stats->collisions = mac_stats->tx_collision;
	stats->rx_length_errors = (mac_stats->rx_gtjumbo +
				   mac_stats->rx_length_error);
	stats->rx_crc_errors = mac_stats->rx_bad;
	stats->rx_frame_errors = mac_stats->rx_align_error;
	stats->rx_fifo_errors = mac_stats->rx_overflow;
	stats->rx_missed_errors = mac_stats->rx_missed;
	stats->tx_window_errors = mac_stats->tx_late_collision;

	stats->rx_errors = (stats->rx_length_errors +
			    stats->rx_crc_errors +
			    stats->rx_frame_errors +
			    mac_stats->rx_symbol_error);
	stats->tx_errors = (stats->tx_window_errors +
			    mac_stats->tx_bad);

	spin_unlock_bh(&efx->stats_lock);

	return stats;
}