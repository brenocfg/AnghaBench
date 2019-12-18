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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_cmd {scalar_t__ autoneg; int speed; int /*<<< orphan*/  duplex; } ;
struct ehea_port {int full_duplex; int /*<<< orphan*/  port_speed; TYPE_1__* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  EHEA_SPEED_AUTONEG ; 
 int EINVAL ; 
 int /*<<< orphan*/  H_SPEED_100M_F ; 
 int /*<<< orphan*/  H_SPEED_100M_H ; 
 int /*<<< orphan*/  H_SPEED_10G_F ; 
 int /*<<< orphan*/  H_SPEED_10M_F ; 
 int /*<<< orphan*/  H_SPEED_10M_H ; 
 int /*<<< orphan*/  H_SPEED_1G_F ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_10000 128 
 int /*<<< orphan*/  ehea_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ehea_set_portspeed (struct ehea_port*,int /*<<< orphan*/ ) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ehea_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct ehea_port *port = netdev_priv(dev);
	int ret = 0;
	u32 sp;

	if (cmd->autoneg == AUTONEG_ENABLE) {
		sp = EHEA_SPEED_AUTONEG;
		goto doit;
	}

	switch (cmd->speed) {
	case SPEED_10:
		if (cmd->duplex == DUPLEX_FULL)
			sp = H_SPEED_10M_F;
		else
			sp = H_SPEED_10M_H;
		break;

	case SPEED_100:
		if (cmd->duplex == DUPLEX_FULL)
			sp = H_SPEED_100M_F;
		else
			sp = H_SPEED_100M_H;
		break;

	case SPEED_1000:
		if (cmd->duplex == DUPLEX_FULL)
			sp = H_SPEED_1G_F;
		else
			ret = -EINVAL;
		break;

	case SPEED_10000:
		if (cmd->duplex == DUPLEX_FULL)
			sp = H_SPEED_10G_F;
		else
			ret = -EINVAL;
		break;

	default:
			ret = -EINVAL;
		break;
	}

	if (ret)
		goto out;
doit:
	ret = ehea_set_portspeed(port, sp);

	if (!ret)
		ehea_info("%s: Port speed succesfully set: %dMbps "
			  "%s Duplex",
			  port->netdev->name, port->port_speed,
			  port->full_duplex == 1 ? "Full" : "Half");
out:
	return ret;
}