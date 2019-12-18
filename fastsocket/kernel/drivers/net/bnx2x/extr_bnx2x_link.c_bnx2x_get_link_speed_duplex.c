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
struct link_vars {int phy_link_up; int duplex; int /*<<< orphan*/  line_speed; int /*<<< orphan*/  mac_type; int /*<<< orphan*/  flow_ctrl; int /*<<< orphan*/  link_status; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {scalar_t__ req_line_speed; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FLOW_CTRL_NONE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int DUPLEX_FULL ; 
 int EINVAL ; 
#define  GP_STATUS_100M 142 
#define  GP_STATUS_10G_CX4 141 
#define  GP_STATUS_10G_HIG 140 
#define  GP_STATUS_10G_KR 139 
#define  GP_STATUS_10G_KX4 138 
#define  GP_STATUS_10G_SFI 137 
#define  GP_STATUS_10G_XFI 136 
#define  GP_STATUS_10M 135 
#define  GP_STATUS_1G 134 
#define  GP_STATUS_1G_KX 133 
#define  GP_STATUS_20G_DXGXS 132 
#define  GP_STATUS_20G_KR2 131 
#define  GP_STATUS_2_5G 130 
#define  GP_STATUS_5G 129 
#define  GP_STATUS_6G 128 
 int /*<<< orphan*/  LINK_1000TFD ; 
 int /*<<< orphan*/  LINK_1000THD ; 
 int /*<<< orphan*/  LINK_100TXFD ; 
 int /*<<< orphan*/  LINK_100TXHD ; 
 int /*<<< orphan*/  LINK_10GTFD ; 
 int /*<<< orphan*/  LINK_10TFD ; 
 int /*<<< orphan*/  LINK_10THD ; 
 int /*<<< orphan*/  LINK_20GTFD ; 
 int /*<<< orphan*/  LINK_2500TFD ; 
 int /*<<< orphan*/  LINK_2500THD ; 
 int /*<<< orphan*/  LINK_STATUS_AUTO_NEGOTIATE_ENABLED ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_UP ; 
 int /*<<< orphan*/  MAC_TYPE_NONE ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_20000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 scalar_t__ SPEED_AUTO_NEG ; 

__attribute__((used)) static int bnx2x_get_link_speed_duplex(struct bnx2x_phy *phy,
				     struct link_params *params,
				      struct link_vars *vars,
				      u16 is_link_up,
				      u16 speed_mask,
				      u16 is_duplex)
{
	struct bnx2x *bp = params->bp;
	if (phy->req_line_speed == SPEED_AUTO_NEG)
		vars->link_status |= LINK_STATUS_AUTO_NEGOTIATE_ENABLED;
	if (is_link_up) {
		DP(NETIF_MSG_LINK, "phy link up\n");

		vars->phy_link_up = 1;
		vars->link_status |= LINK_STATUS_LINK_UP;

		switch (speed_mask) {
		case GP_STATUS_10M:
			vars->line_speed = SPEED_10;
			if (is_duplex == DUPLEX_FULL)
				vars->link_status |= LINK_10TFD;
			else
				vars->link_status |= LINK_10THD;
			break;

		case GP_STATUS_100M:
			vars->line_speed = SPEED_100;
			if (is_duplex == DUPLEX_FULL)
				vars->link_status |= LINK_100TXFD;
			else
				vars->link_status |= LINK_100TXHD;
			break;

		case GP_STATUS_1G:
		case GP_STATUS_1G_KX:
			vars->line_speed = SPEED_1000;
			if (is_duplex == DUPLEX_FULL)
				vars->link_status |= LINK_1000TFD;
			else
				vars->link_status |= LINK_1000THD;
			break;

		case GP_STATUS_2_5G:
			vars->line_speed = SPEED_2500;
			if (is_duplex == DUPLEX_FULL)
				vars->link_status |= LINK_2500TFD;
			else
				vars->link_status |= LINK_2500THD;
			break;

		case GP_STATUS_5G:
		case GP_STATUS_6G:
			DP(NETIF_MSG_LINK,
				 "link speed unsupported  gp_status 0x%x\n",
				  speed_mask);
			return -EINVAL;

		case GP_STATUS_10G_KX4:
		case GP_STATUS_10G_HIG:
		case GP_STATUS_10G_CX4:
		case GP_STATUS_10G_KR:
		case GP_STATUS_10G_SFI:
		case GP_STATUS_10G_XFI:
			vars->line_speed = SPEED_10000;
			vars->link_status |= LINK_10GTFD;
			break;
		case GP_STATUS_20G_DXGXS:
		case GP_STATUS_20G_KR2:
			vars->line_speed = SPEED_20000;
			vars->link_status |= LINK_20GTFD;
			break;
		default:
			DP(NETIF_MSG_LINK,
				  "link speed unsupported gp_status 0x%x\n",
				  speed_mask);
			return -EINVAL;
		}
	} else { /* link_down */
		DP(NETIF_MSG_LINK, "phy link down\n");

		vars->phy_link_up = 0;

		vars->duplex = DUPLEX_FULL;
		vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
		vars->mac_type = MAC_TYPE_NONE;
	}
	DP(NETIF_MSG_LINK, " phy_link_up %x line_speed %d\n",
		    vars->phy_link_up, vars->line_speed);
	return 0;
}