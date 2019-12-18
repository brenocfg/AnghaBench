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
struct vport {int dummy; } ;
struct ovs_vport_stats {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_packets; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 struct vport* ovs_internal_dev_get_vport (struct net_device*) ; 
 int /*<<< orphan*/  ovs_vport_get_stats (struct vport*,struct ovs_vport_stats*) ; 

__attribute__((used)) static struct net_device_stats *internal_dev_get_stats(struct net_device *netdev)
{
	struct vport *vport = ovs_internal_dev_get_vport(netdev);
	struct ovs_vport_stats vport_stats;
	struct net_device_stats *stats = &netdev->stats;

	ovs_vport_get_stats(vport, &vport_stats);

	/* The tx and rx stats need to be swapped because the
	 * switch and host OS have opposite perspectives. */
	stats->rx_packets	= vport_stats.tx_packets;
	stats->tx_packets	= vport_stats.rx_packets;
	stats->rx_bytes		= vport_stats.tx_bytes;
	stats->tx_bytes		= vport_stats.rx_bytes;
	stats->rx_errors	= vport_stats.tx_errors;
	stats->tx_errors	= vport_stats.rx_errors;
	stats->rx_dropped	= vport_stats.tx_dropped;
	stats->tx_dropped	= vport_stats.rx_dropped;

	return stats;
}