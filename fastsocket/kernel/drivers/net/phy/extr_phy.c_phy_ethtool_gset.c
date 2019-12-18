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
struct phy_device {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  addr; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_cmd {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_MII ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 

int phy_ethtool_gset(struct phy_device *phydev, struct ethtool_cmd *cmd)
{
	cmd->supported = phydev->supported;

	cmd->advertising = phydev->advertising;

	cmd->speed = phydev->speed;
	cmd->duplex = phydev->duplex;
	cmd->port = PORT_MII;
	cmd->phy_address = phydev->addr;
	cmd->transceiver = XCVR_EXTERNAL;
	cmd->autoneg = phydev->autoneg;

	return 0;
}