#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct vnic_stats {int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct enic {int dummy; } ;
struct TYPE_4__ {size_t offset; } ;
struct TYPE_3__ {size_t offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  enic_dev_stats_dump (struct enic*,struct vnic_stats**) ; 
 unsigned int enic_n_rx_stats ; 
 unsigned int enic_n_tx_stats ; 
 TYPE_2__* enic_rx_stats ; 
 TYPE_1__* enic_tx_stats ; 
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void enic_get_ethtool_stats(struct net_device *netdev,
	struct ethtool_stats *stats, u64 *data)
{
	struct enic *enic = netdev_priv(netdev);
	struct vnic_stats *vstats;
	unsigned int i;

	enic_dev_stats_dump(enic, &vstats);

	for (i = 0; i < enic_n_tx_stats; i++)
		*(data++) = ((u64 *)&vstats->tx)[enic_tx_stats[i].offset];
	for (i = 0; i < enic_n_rx_stats; i++)
		*(data++) = ((u64 *)&vstats->rx)[enic_rx_stats[i].offset];
}