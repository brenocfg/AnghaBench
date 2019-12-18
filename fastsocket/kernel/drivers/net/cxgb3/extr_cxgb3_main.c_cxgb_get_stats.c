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
struct net_device_stats {scalar_t__ tx_window_errors; scalar_t__ tx_heartbeat_errors; int /*<<< orphan*/  tx_fifo_errors; scalar_t__ tx_carrier_errors; scalar_t__ tx_aborted_errors; int /*<<< orphan*/  rx_missed_errors; scalar_t__ rx_fifo_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_over_errors; scalar_t__ rx_length_errors; scalar_t__ rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct port_info {int /*<<< orphan*/  mac; struct net_device_stats netstats; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct mac_stats {int /*<<< orphan*/  tx_underrun; int /*<<< orphan*/  rx_cong_drops; scalar_t__ rx_fifo_ovfl; scalar_t__ rx_symbol_errs; scalar_t__ rx_fcs_errs; scalar_t__ rx_too_long; scalar_t__ rx_jabber; scalar_t__ rx_short; int /*<<< orphan*/  rx_mcast_frames; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  rx_octets; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_octets; } ;
struct adapter {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct mac_stats* t3_mac_update_stats (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net_device_stats *cxgb_get_stats(struct net_device *dev)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	struct net_device_stats *ns = &pi->netstats;
	const struct mac_stats *pstats;

	spin_lock(&adapter->stats_lock);
	pstats = t3_mac_update_stats(&pi->mac);
	spin_unlock(&adapter->stats_lock);

	ns->tx_bytes = pstats->tx_octets;
	ns->tx_packets = pstats->tx_frames;
	ns->rx_bytes = pstats->rx_octets;
	ns->rx_packets = pstats->rx_frames;
	ns->multicast = pstats->rx_mcast_frames;

	ns->tx_errors = pstats->tx_underrun;
	ns->rx_errors = pstats->rx_symbol_errs + pstats->rx_fcs_errs +
	    pstats->rx_too_long + pstats->rx_jabber + pstats->rx_short +
	    pstats->rx_fifo_ovfl;

	/* detailed rx_errors */
	ns->rx_length_errors = pstats->rx_jabber + pstats->rx_too_long;
	ns->rx_over_errors = 0;
	ns->rx_crc_errors = pstats->rx_fcs_errs;
	ns->rx_frame_errors = pstats->rx_symbol_errs;
	ns->rx_fifo_errors = pstats->rx_fifo_ovfl;
	ns->rx_missed_errors = pstats->rx_cong_drops;

	/* detailed tx_errors */
	ns->tx_aborted_errors = 0;
	ns->tx_carrier_errors = 0;
	ns->tx_fifo_errors = pstats->tx_underrun;
	ns->tx_heartbeat_errors = 0;
	ns->tx_window_errors = 0;
	return ns;
}