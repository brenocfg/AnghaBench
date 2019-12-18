#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device_stats {int dummy; } ;
struct net_device {struct net_device_stats stats; } ;
struct igb_adapter {int num_tx_queues; int num_rx_queues; TYPE_2__** rx_ring; TYPE_1__** tx_ring; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_8__ {int stat_offset; int sizeof_stat; } ;
struct TYPE_7__ {int stat_offset; int sizeof_stat; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_stats; } ;

/* Variables and functions */
 int IGB_GLOBAL_STATS_LEN ; 
 int IGB_NETDEV_STATS_LEN ; 
 int IGB_RX_QUEUE_STATS_LEN ; 
 int IGB_TX_QUEUE_STATS_LEN ; 
 TYPE_4__* igb_gstrings_net_stats ; 
 TYPE_3__* igb_gstrings_stats ; 
 int /*<<< orphan*/  igb_update_stats (struct igb_adapter*) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void igb_get_ethtool_stats(struct net_device *netdev,
				  struct ethtool_stats *stats, u64 *data)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct net_device_stats *net_stats = &netdev->stats;
	u64 *queue_stat;
	int i, j, k;
	char *p;

	igb_update_stats(adapter);

	for (i = 0; i < IGB_GLOBAL_STATS_LEN; i++) {
		p = (char *)adapter + igb_gstrings_stats[i].stat_offset;
		data[i] = (igb_gstrings_stats[i].sizeof_stat ==
			sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}
	for (j = 0; j < IGB_NETDEV_STATS_LEN; j++, i++) {
		p = (char *)net_stats + igb_gstrings_net_stats[j].stat_offset;
		data[i] = (igb_gstrings_net_stats[j].sizeof_stat ==
			sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}
	for (j = 0; j < adapter->num_tx_queues; j++) {
		queue_stat = (u64 *)&adapter->tx_ring[j]->tx_stats;
		for (k = 0; k < IGB_TX_QUEUE_STATS_LEN; k++, i++)
			data[i] = queue_stat[k];
	}
	for (j = 0; j < adapter->num_rx_queues; j++) {
		queue_stat = (u64 *)&adapter->rx_ring[j]->rx_stats;
		for (k = 0; k < IGB_RX_QUEUE_STATS_LEN; k++, i++)
			data[i] = queue_stat[k];
	}
}