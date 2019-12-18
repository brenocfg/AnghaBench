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
struct phy_device {scalar_t__ addr; scalar_t__ autoneg; scalar_t__ speed; scalar_t__ duplex; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_cmd {scalar_t__ phy_address; scalar_t__ autoneg; scalar_t__ speed; scalar_t__ duplex; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_Autoneg ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 

int phy_ethtool_sset(struct phy_device *phydev, struct ethtool_cmd *cmd)
{
	if (cmd->phy_address != phydev->addr)
		return -EINVAL;

	/* We make sure that we don't pass unsupported
	 * values in to the PHY */
	cmd->advertising &= phydev->supported;

	/* Verify the settings we care about. */
	if (cmd->autoneg != AUTONEG_ENABLE && cmd->autoneg != AUTONEG_DISABLE)
		return -EINVAL;

	if (cmd->autoneg == AUTONEG_ENABLE && cmd->advertising == 0)
		return -EINVAL;

	if (cmd->autoneg == AUTONEG_DISABLE
			&& ((cmd->speed != SPEED_1000
					&& cmd->speed != SPEED_100
					&& cmd->speed != SPEED_10)
				|| (cmd->duplex != DUPLEX_HALF
					&& cmd->duplex != DUPLEX_FULL)))
		return -EINVAL;

	phydev->autoneg = cmd->autoneg;

	phydev->speed = cmd->speed;

	phydev->advertising = cmd->advertising;

	if (AUTONEG_ENABLE == cmd->autoneg)
		phydev->advertising |= ADVERTISED_Autoneg;
	else
		phydev->advertising &= ~ADVERTISED_Autoneg;

	phydev->duplex = cmd->duplex;

	/* Restart the PHY */
	phy_start_aneg(phydev);

	return 0;
}