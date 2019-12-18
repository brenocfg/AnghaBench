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
struct net_device {int dummy; } ;
struct ethtool_channels {scalar_t__ combined_count; scalar_t__ other_count; scalar_t__ tx_count; scalar_t__ rx_count; } ;
struct be_adapter {scalar_t__ cfg_num_qs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ be_max_qs (struct be_adapter*) ; 
 int be_update_queues (struct be_adapter*) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_set_channels(struct net_device  *netdev,
			   struct ethtool_channels *ch)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	if (ch->rx_count || ch->tx_count || ch->other_count ||
	    !ch->combined_count || ch->combined_count > be_max_qs(adapter))
		return -EINVAL;

	adapter->cfg_num_qs = ch->combined_count;

	return be_update_queues(adapter);
}