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
struct net_device_stats {scalar_t__ rx_crc_errors; int /*<<< orphan*/  rx_over_errors; scalar_t__ rx_length_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_errors; scalar_t__ rx_errors; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ crc_err; int /*<<< orphan*/  rx_ov_flow; scalar_t__ length_err; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multircv; int /*<<< orphan*/  max_pkt_error; scalar_t__ other_errors; scalar_t__ code_violations; scalar_t__ alignment_err; int /*<<< orphan*/  opackets; int /*<<< orphan*/  ipackets; } ;
struct et131x_adapter {TYPE_1__ Stats; struct net_device_stats net_stats; } ;
typedef  TYPE_1__ CE_STATS_t ;

/* Variables and functions */
 struct et131x_adapter* netdev_priv (struct net_device*) ; 

struct net_device_stats *et131x_stats(struct net_device *netdev)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);
	struct net_device_stats *stats = &adapter->net_stats;
	CE_STATS_t *devstat = &adapter->Stats;

	stats->rx_packets = devstat->ipackets;
	stats->tx_packets = devstat->opackets;
	stats->rx_errors = devstat->length_err + devstat->alignment_err +
	    devstat->crc_err + devstat->code_violations + devstat->other_errors;
	stats->tx_errors = devstat->max_pkt_error;
	stats->multicast = devstat->multircv;
	stats->collisions = devstat->collisions;

	stats->rx_length_errors = devstat->length_err;
	stats->rx_over_errors = devstat->rx_ov_flow;
	stats->rx_crc_errors = devstat->crc_err;

	/* NOTE: These stats don't have corresponding values in CE_STATS,
	 * so we're going to have to update these directly from within the
	 * TX/RX code
	 */
	/* stats->rx_bytes            = 20; devstat->; */
	/* stats->tx_bytes            = 20;  devstat->; */
	/* stats->rx_dropped          = devstat->; */
	/* stats->tx_dropped          = devstat->; */

	/*  NOTE: Not used, can't find analogous statistics */
	/* stats->rx_frame_errors     = devstat->; */
	/* stats->rx_fifo_errors      = devstat->; */
	/* stats->rx_missed_errors    = devstat->; */

	/* stats->tx_aborted_errors   = devstat->; */
	/* stats->tx_carrier_errors   = devstat->; */
	/* stats->tx_fifo_errors      = devstat->; */
	/* stats->tx_heartbeat_errors = devstat->; */
	/* stats->tx_window_errors    = devstat->; */
	return stats;
}