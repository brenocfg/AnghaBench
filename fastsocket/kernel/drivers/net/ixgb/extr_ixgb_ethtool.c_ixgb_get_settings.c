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
struct ixgb_adapter {int /*<<< orphan*/  netdev; } ;
struct ethtool_cmd {int supported; int advertising; int speed; int duplex; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_FIBRE ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int SPEED_10000 ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgb_get_settings(struct net_device *netdev, struct ethtool_cmd *ecmd)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);

	ecmd->supported = (SUPPORTED_10000baseT_Full | SUPPORTED_FIBRE);
	ecmd->advertising = (ADVERTISED_10000baseT_Full | ADVERTISED_FIBRE);
	ecmd->port = PORT_FIBRE;
	ecmd->transceiver = XCVR_EXTERNAL;

	if (netif_carrier_ok(adapter->netdev)) {
		ecmd->speed = SPEED_10000;
		ecmd->duplex = DUPLEX_FULL;
	} else {
		ecmd->speed = -1;
		ecmd->duplex = -1;
	}

	ecmd->autoneg = AUTONEG_DISABLE;
	return 0;
}