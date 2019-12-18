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
struct net_device_stats {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int dummy; } ;
struct myri10ge_slice_netstats {scalar_t__ tx_dropped; scalar_t__ rx_dropped; scalar_t__ tx_bytes; scalar_t__ rx_bytes; scalar_t__ tx_packets; scalar_t__ rx_packets; } ;
struct myri10ge_priv {int num_slices; int /*<<< orphan*/  stats_lock; TYPE_1__* ss; struct net_device_stats stats; } ;
struct TYPE_2__ {struct myri10ge_slice_netstats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct net_device_stats*,int /*<<< orphan*/ ,int) ; 
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net_device_stats *myri10ge_get_stats(struct net_device *dev)
{
	struct myri10ge_priv *mgp = netdev_priv(dev);
	struct myri10ge_slice_netstats *slice_stats;
	struct net_device_stats *stats = &mgp->stats;
	int i;

	spin_lock(&mgp->stats_lock);
	memset(stats, 0, sizeof(*stats));
	for (i = 0; i < mgp->num_slices; i++) {
		slice_stats = &mgp->ss[i].stats;
		stats->rx_packets += slice_stats->rx_packets;
		stats->tx_packets += slice_stats->tx_packets;
		stats->rx_bytes += slice_stats->rx_bytes;
		stats->tx_bytes += slice_stats->tx_bytes;
		stats->rx_dropped += slice_stats->rx_dropped;
		stats->tx_dropped += slice_stats->tx_dropped;
	}
	spin_unlock(&mgp->stats_lock);
	return stats;
}