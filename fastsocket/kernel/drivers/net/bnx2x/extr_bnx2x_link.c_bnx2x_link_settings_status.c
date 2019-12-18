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
struct link_vars {int duplex; int link_status; int flow_ctrl; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {scalar_t__ req_line_speed; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int EINVAL ; 
 int GP_STATUS_SPEED_MASK ; 
 int LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE ; 
 int MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX ; 
 int MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KR ; 
 int MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4 ; 
 int /*<<< orphan*/  MDIO_CL73_IEEEB1_AN_LP_ADV2 ; 
 int /*<<< orphan*/  MDIO_GP_STATUS_TOP_AN_STATUS1 ; 
 int MDIO_GP_STATUS_TOP_AN_STATUS1_DUPLEX_STATUS ; 
 int MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS ; 
 int /*<<< orphan*/  MDIO_OVER_1G_LP_UP1 ; 
 int MDIO_OVER_1G_UP1_10G ; 
 int MDIO_OVER_1G_UP1_10GH ; 
 int MDIO_OVER_1G_UP1_2_5G ; 
 int /*<<< orphan*/  MDIO_REG_BANK_CL73_IEEEB1 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_GP_STATUS ; 
 int /*<<< orphan*/  MDIO_REG_BANK_OVER_1G ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ SINGLE_MEDIA_DIRECT (struct link_params*) ; 
 scalar_t__ SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  bnx2x_check_fallback_to_cl37 (struct bnx2x_phy*,struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_flow_ctrl_resolve (struct bnx2x_phy*,struct link_params*,struct link_vars*,int) ; 
 int bnx2x_get_link_speed_duplex (struct bnx2x_phy*,struct link_params*,struct link_vars*,int,int,int) ; 
 int /*<<< orphan*/  bnx2x_xgxs_an_resolve (struct bnx2x_phy*,struct link_params*,struct link_vars*,int) ; 

__attribute__((used)) static int bnx2x_link_settings_status(struct bnx2x_phy *phy,
				      struct link_params *params,
				      struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;

	u16 gp_status, duplex = DUPLEX_HALF, link_up = 0, speed_mask;
	int rc = 0;

	/* Read gp_status */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_GP_STATUS,
			  MDIO_GP_STATUS_TOP_AN_STATUS1,
			  &gp_status);
	if (gp_status & MDIO_GP_STATUS_TOP_AN_STATUS1_DUPLEX_STATUS)
		duplex = DUPLEX_FULL;
	if (gp_status & MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS)
		link_up = 1;
	speed_mask = gp_status & GP_STATUS_SPEED_MASK;
	DP(NETIF_MSG_LINK, "gp_status 0x%x, is_link_up %d, speed_mask 0x%x\n",
		       gp_status, link_up, speed_mask);
	rc = bnx2x_get_link_speed_duplex(phy, params, vars, link_up, speed_mask,
					 duplex);
	if (rc == -EINVAL)
		return rc;

	if (gp_status & MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS) {
		if (SINGLE_MEDIA_DIRECT(params)) {
			vars->duplex = duplex;
			bnx2x_flow_ctrl_resolve(phy, params, vars, gp_status);
			if (phy->req_line_speed == SPEED_AUTO_NEG)
				bnx2x_xgxs_an_resolve(phy, params, vars,
						      gp_status);
		}
	} else { /* Link_down */
		if ((phy->req_line_speed == SPEED_AUTO_NEG) &&
		    SINGLE_MEDIA_DIRECT(params)) {
			/* Check signal is detected */
			bnx2x_check_fallback_to_cl37(phy, params);
		}
	}

	/* Read LP advertised speeds*/
	if (SINGLE_MEDIA_DIRECT(params) &&
	    (vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE)) {
		u16 val;

		CL22_RD_OVER_CL45(bp, phy, MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_LP_ADV2, &val);

		if (val & MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX)
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;
		if (val & (MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4 |
			   MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KR))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;

		CL22_RD_OVER_CL45(bp, phy, MDIO_REG_BANK_OVER_1G,
				  MDIO_OVER_1G_LP_UP1, &val);

		if (val & MDIO_OVER_1G_UP1_2_5G)
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE;
		if (val & (MDIO_OVER_1G_UP1_10G | MDIO_OVER_1G_UP1_10GH))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;
	}

	DP(NETIF_MSG_LINK, "duplex %x  flow_ctrl 0x%x link_status 0x%x\n",
		   vars->duplex, vars->flow_ctrl, vars->link_status);
	return rc;
}