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
struct vmxnet3_adapter {int link_speed; } ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int supported; int duplex; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  port; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_TP ; 
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  PORT_TP ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
vmxnet3_get_settings(struct net_device *netdev, struct ethtool_cmd *ecmd)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);

	ecmd->supported = SUPPORTED_10000baseT_Full | SUPPORTED_1000baseT_Full |
			  SUPPORTED_TP;
	ecmd->advertising = ADVERTISED_TP;
	ecmd->port = PORT_TP;
	ecmd->transceiver = XCVR_INTERNAL;

	if (adapter->link_speed) {
		ethtool_cmd_speed_set(ecmd, adapter->link_speed);
		ecmd->duplex = DUPLEX_FULL;
	} else {
		ethtool_cmd_speed_set(ecmd, -1);
		ecmd->duplex = -1;
	}
	return 0;
}