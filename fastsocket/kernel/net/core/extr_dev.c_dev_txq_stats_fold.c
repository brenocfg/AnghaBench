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
struct netdev_queue {scalar_t__ tx_dropped; scalar_t__ tx_packets; scalar_t__ tx_bytes; } ;
struct net_device_stats {unsigned long tx_bytes; unsigned long tx_packets; unsigned long tx_dropped; } ;
struct net_device {unsigned int num_tx_queues; } ;

/* Variables and functions */
 struct netdev_queue* netdev_get_tx_queue (struct net_device const*,unsigned int) ; 

void dev_txq_stats_fold(const struct net_device *dev,
			struct net_device_stats *stats)
{
	unsigned long tx_bytes = 0, tx_packets = 0, tx_dropped = 0;
	unsigned int i;
	struct netdev_queue *txq;

	for (i = 0; i < dev->num_tx_queues; i++) {
		txq = netdev_get_tx_queue(dev, i);
		tx_bytes   += txq->tx_bytes;
		tx_packets += txq->tx_packets;
		tx_dropped += txq->tx_dropped;
	}
	if (tx_bytes || tx_packets || tx_dropped) {
		stats->tx_bytes   = tx_bytes;
		stats->tx_packets = tx_packets;
		stats->tx_dropped = tx_dropped;
	}
}