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
 scalar_t__ netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static int vxge_ethtool_gset(struct net_device *dev, struct ethtool_cmd *info)
{
	info->supported = (SUPPORTED_10000baseT_Full | SUPPORTED_FIBRE);
	info->advertising = (ADVERTISED_10000baseT_Full | ADVERTISED_FIBRE);
	info->port = PORT_FIBRE;

	info->transceiver = XCVR_EXTERNAL;

	if (netif_carrier_ok(dev)) {
		info->speed = SPEED_10000;
		info->duplex = DUPLEX_FULL;
	} else {
		info->speed = -1;
		info->duplex = -1;
	}

	info->autoneg = AUTONEG_DISABLE;
	return 0;
}