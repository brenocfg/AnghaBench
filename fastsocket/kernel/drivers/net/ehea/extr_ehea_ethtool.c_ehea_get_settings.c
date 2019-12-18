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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ethtool_cmd {int duplex; scalar_t__ speed; int supported; int advertising; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  port; } ;
struct ehea_port {int port_speed; int full_duplex; int autoneg; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
#define  EHEA_SPEED_100M 131 
#define  EHEA_SPEED_10G 130 
#define  EHEA_SPEED_10M 129 
#define  EHEA_SPEED_1G 128 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 scalar_t__ SPEED_10000 ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_TP ; 
 int ehea_sense_port_attr (struct ehea_port*) ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static int ehea_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct ehea_port *port = netdev_priv(dev);
	u32 speed;
	int ret;

	ret = ehea_sense_port_attr(port);

	if (ret)
		return ret;

	if (netif_carrier_ok(dev)) {
		switch (port->port_speed) {
		case EHEA_SPEED_10M:
			speed = SPEED_10;
			break;
		case EHEA_SPEED_100M:
			speed = SPEED_100;
			break;
		case EHEA_SPEED_1G:
			speed = SPEED_1000;
			break;
		case EHEA_SPEED_10G:
			speed = SPEED_10000;
			break;
		default:
			speed = -1;
			break; /* BUG */
		}
		cmd->duplex = port->full_duplex == 1 ?
						     DUPLEX_FULL : DUPLEX_HALF;
	} else {
		speed = ~0;
		cmd->duplex = -1;
	}
	ethtool_cmd_speed_set(cmd, speed);

	if (cmd->speed == SPEED_10000) {
		cmd->supported = (SUPPORTED_10000baseT_Full | SUPPORTED_FIBRE);
		cmd->advertising = (ADVERTISED_10000baseT_Full | ADVERTISED_FIBRE);
		cmd->port = PORT_FIBRE;
	} else {
		cmd->supported = (SUPPORTED_1000baseT_Full | SUPPORTED_100baseT_Full
			       | SUPPORTED_100baseT_Half | SUPPORTED_10baseT_Full
			       | SUPPORTED_10baseT_Half | SUPPORTED_Autoneg
			       | SUPPORTED_TP);
		cmd->advertising = (ADVERTISED_1000baseT_Full | ADVERTISED_Autoneg
				 | ADVERTISED_TP);
		cmd->port = PORT_TP;
	}

	cmd->autoneg = port->autoneg == 1 ? AUTONEG_ENABLE : AUTONEG_DISABLE;

	return 0;
}