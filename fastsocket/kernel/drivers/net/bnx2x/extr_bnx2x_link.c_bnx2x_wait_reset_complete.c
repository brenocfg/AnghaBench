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
typedef  int u16 ;
struct link_params {int /*<<< orphan*/  port; } ;
struct bnx2x_phy {scalar_t__ type; } ;
struct bnx2x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_CTRL ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE ; 
 int /*<<< orphan*/  bnx2x_cl22_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static u16 bnx2x_wait_reset_complete(struct bnx2x *bp,
				     struct bnx2x_phy *phy,
				     struct link_params *params)
{
	u16 cnt, ctrl;
	/* Wait for soft reset to get cleared up to 1 sec */
	for (cnt = 0; cnt < 1000; cnt++) {
		if (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE)
			bnx2x_cl22_read(bp, phy,
				MDIO_PMA_REG_CTRL, &ctrl);
		else
			bnx2x_cl45_read(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_CTRL, &ctrl);
		if (!(ctrl & (1<<15)))
			break;
		usleep_range(1000, 2000);
	}

	if (cnt == 1000)
		netdev_err(bp->dev,  "Warning: PHY was not initialized,"
				      " Port %d\n",
			 params->port);
	DP(NETIF_MSG_LINK, "control reg 0x%x (after %d ms)\n", ctrl, cnt);
	return cnt;
}