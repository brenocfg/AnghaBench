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
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  data; int /*<<< orphan*/  flow_type; } ;
struct be_adapter {int /*<<< orphan*/  num_rx_qs; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_GRXFH 129 
#define  ETHTOOL_GRXRINGS 128 
 int /*<<< orphan*/  be_get_rss_hash_opts (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_multi_rxq (struct be_adapter*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_get_rxnfc(struct net_device *netdev, struct ethtool_rxnfc *cmd,
		      void *rule_locs)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	if (!be_multi_rxq(adapter)) {
		dev_info(&adapter->pdev->dev,
			 "ethtool::get_rxnfc: RX flow hashing is disabled\n");
		return -EINVAL;
	}

	switch (cmd->cmd) {
	case ETHTOOL_GRXFH:
		cmd->data = be_get_rss_hash_opts(adapter, cmd->flow_type);
		break;
	case ETHTOOL_GRXRINGS:
		cmd->data = adapter->num_rx_qs - 1;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}