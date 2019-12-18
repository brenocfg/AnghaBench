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
struct ethtool_cmd {int supported; int advertising; int duplex; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  port; } ;
struct enic {int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_FIBRE ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int vnic_dev_port_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_get_settings(struct net_device *netdev,
	struct ethtool_cmd *ecmd)
{
	struct enic *enic = netdev_priv(netdev);

	ecmd->supported = (SUPPORTED_10000baseT_Full | SUPPORTED_FIBRE);
	ecmd->advertising = (ADVERTISED_10000baseT_Full | ADVERTISED_FIBRE);
	ecmd->port = PORT_FIBRE;
	ecmd->transceiver = XCVR_EXTERNAL;

	if (netif_carrier_ok(netdev)) {
		ethtool_cmd_speed_set(ecmd, vnic_dev_port_speed(enic->vdev));
		ecmd->duplex = DUPLEX_FULL;
	} else {
		ethtool_cmd_speed_set(ecmd, -1);
		ecmd->duplex = -1;
	}

	ecmd->autoneg = AUTONEG_DISABLE;

	return 0;
}