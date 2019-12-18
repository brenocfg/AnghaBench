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
struct mv643xx_eth_private {int /*<<< orphan*/  phy; } ;
struct ethtool_cmd {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_1000baseT_Half ; 
 int /*<<< orphan*/  SUPPORTED_1000baseT_Half ; 
 int phy_ethtool_gset (int /*<<< orphan*/ ,struct ethtool_cmd*) ; 
 int phy_read_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv643xx_eth_get_settings_phy(struct mv643xx_eth_private *mp,
			     struct ethtool_cmd *cmd)
{
	int err;

	err = phy_read_status(mp->phy);
	if (err == 0)
		err = phy_ethtool_gset(mp->phy, cmd);

	/*
	 * The MAC does not support 1000baseT_Half.
	 */
	cmd->supported &= ~SUPPORTED_1000baseT_Half;
	cmd->advertising &= ~ADVERTISED_1000baseT_Half;

	return err;
}