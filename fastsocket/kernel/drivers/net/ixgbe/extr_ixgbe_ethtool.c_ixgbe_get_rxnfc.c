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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int /*<<< orphan*/  fdir_filter_count; int /*<<< orphan*/  num_rx_queues; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  rule_cnt; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXCLSRLALL 132 
#define  ETHTOOL_GRXCLSRLCNT 131 
#define  ETHTOOL_GRXCLSRULE 130 
#define  ETHTOOL_GRXFH 129 
#define  ETHTOOL_GRXRINGS 128 
 int ixgbe_get_ethtool_fdir_all (struct ixgbe_adapter*,struct ethtool_rxnfc*,int /*<<< orphan*/ *) ; 
 int ixgbe_get_ethtool_fdir_entry (struct ixgbe_adapter*,struct ethtool_rxnfc*) ; 
 int ixgbe_get_rss_hash_opts (struct ixgbe_adapter*,struct ethtool_rxnfc*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_get_rxnfc(struct net_device *dev, struct ethtool_rxnfc *cmd,
			   void *rule_locs)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	int ret = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOL_GRXRINGS:
		cmd->data = adapter->num_rx_queues;
		ret = 0;
		break;
	case ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = adapter->fdir_filter_count;
		ret = 0;
		break;
	case ETHTOOL_GRXCLSRULE:
		ret = ixgbe_get_ethtool_fdir_entry(adapter, cmd);
		break;
	case ETHTOOL_GRXCLSRLALL:
		ret = ixgbe_get_ethtool_fdir_all(adapter, cmd,
						 (u32 *)rule_locs);
		break;
	case ETHTOOL_GRXFH:
		ret = ixgbe_get_rss_hash_opts(adapter, cmd);
		break;
	default:
		break;
	}

	return ret;
}