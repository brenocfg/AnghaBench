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
typedef  int u8 ;
typedef  int u16 ;
struct link_vars {int line_speed; scalar_t__ duplex; int /*<<< orphan*/  link_status; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {scalar_t__ type; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int /*<<< orphan*/  LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_100T4_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_10THD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_PARALLEL_DETECTION_USED ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int MDIO_AN_REG_1000T_STATUS ; 
 int /*<<< orphan*/  MDIO_AN_REG_8481_EXPANSION_REG_ACCESS ; 
 int MDIO_AN_REG_8481_EXPANSION_REG_RD_RW ; 
 int MDIO_AN_REG_8481_LEGACY_AN_EXPANSION ; 
 int MDIO_AN_REG_8481_LEGACY_MII_STATUS ; 
 int MDIO_AN_REG_CL37_FC_LP ; 
 int MDIO_AN_REG_MASTER_STATUS ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int MDIO_PMA_REG_8481_PMD_SIGNAL ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833 ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834 ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SPEED_10000 ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_eee_an_resolve (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_ext_phy_10G_an_resolve (struct bnx2x*,struct bnx2x_phy*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_ext_phy_resolve_fc (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 

__attribute__((used)) static u8 bnx2x_848xx_read_status(struct bnx2x_phy *phy,
				  struct link_params *params,
				  struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	u16 val, val1, val2;
	u8 link_up = 0;


	/* Check 10G-BaseT link status */
	/* Check PMD signal ok */
	bnx2x_cl45_read(bp, phy,
			MDIO_AN_DEVAD, 0xFFFA, &val1);
	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_8481_PMD_SIGNAL,
			&val2);
	DP(NETIF_MSG_LINK, "BCM848xx: PMD_SIGNAL 1.a811 = 0x%x\n", val2);

	/* Check link 10G */
	if (val2 & (1<<11)) {
		vars->line_speed = SPEED_10000;
		vars->duplex = DUPLEX_FULL;
		link_up = 1;
		bnx2x_ext_phy_10G_an_resolve(bp, phy, vars);
	} else { /* Check Legacy speed link */
		u16 legacy_status, legacy_speed;

		/* Enable expansion register 0x42 (Operation mode status) */
		bnx2x_cl45_write(bp, phy,
				 MDIO_AN_DEVAD,
				 MDIO_AN_REG_8481_EXPANSION_REG_ACCESS, 0xf42);

		/* Get legacy speed operation status */
		bnx2x_cl45_read(bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_8481_EXPANSION_REG_RD_RW,
				&legacy_status);

		DP(NETIF_MSG_LINK, "Legacy speed status = 0x%x\n",
		   legacy_status);
		link_up = ((legacy_status & (1<<11)) == (1<<11));
		legacy_speed = (legacy_status & (3<<9));
		if (legacy_speed == (0<<9))
			vars->line_speed = SPEED_10;
		else if (legacy_speed == (1<<9))
			vars->line_speed = SPEED_100;
		else if (legacy_speed == (2<<9))
			vars->line_speed = SPEED_1000;
		else { /* Should not happen: Treat as link down */
			vars->line_speed = 0;
			link_up = 0;
		}

		if (link_up) {
			if (legacy_status & (1<<8))
				vars->duplex = DUPLEX_FULL;
			else
				vars->duplex = DUPLEX_HALF;

			DP(NETIF_MSG_LINK,
			   "Link is up in %dMbps, is_duplex_full= %d\n",
			   vars->line_speed,
			   (vars->duplex == DUPLEX_FULL));
			/* Check legacy speed AN resolution */
			bnx2x_cl45_read(bp, phy,
					MDIO_AN_DEVAD,
					MDIO_AN_REG_8481_LEGACY_MII_STATUS,
					&val);
			if (val & (1<<5))
				vars->link_status |=
					LINK_STATUS_AUTO_NEGOTIATE_COMPLETE;
			bnx2x_cl45_read(bp, phy,
					MDIO_AN_DEVAD,
					MDIO_AN_REG_8481_LEGACY_AN_EXPANSION,
					&val);
			if ((val & (1<<0)) == 0)
				vars->link_status |=
					LINK_STATUS_PARALLEL_DETECTION_USED;
		}
	}
	if (link_up) {
		DP(NETIF_MSG_LINK, "BCM848x3: link speed is %d\n",
			   vars->line_speed);
		bnx2x_ext_phy_resolve_fc(phy, params, vars);

		/* Read LP advertised speeds */
		bnx2x_cl45_read(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_CL37_FC_LP, &val);
		if (val & (1<<5))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10THD_CAPABLE;
		if (val & (1<<6))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE;
		if (val & (1<<7))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE;
		if (val & (1<<8))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE;
		if (val & (1<<9))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_100T4_CAPABLE;

		bnx2x_cl45_read(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_1000T_STATUS, &val);

		if (val & (1<<10))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE;
		if (val & (1<<11))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;

		bnx2x_cl45_read(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_MASTER_STATUS, &val);

		if (val & (1<<11))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;

		/* Determine if EEE was negotiated */
		if ((phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833) ||
		    (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834))
			bnx2x_eee_an_resolve(phy, params, vars);
	}

	return link_up;
}