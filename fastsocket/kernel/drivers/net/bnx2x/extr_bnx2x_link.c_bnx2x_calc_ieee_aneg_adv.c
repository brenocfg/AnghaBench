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
typedef  int /*<<< orphan*/  u16 ;
struct link_params {int /*<<< orphan*/  req_fc_auto_adv; struct bnx2x* bp; } ;
struct bnx2x_phy {int req_flow_ctrl; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
#define  BNX2X_FLOW_CTRL_AUTO 132 
#define  BNX2X_FLOW_CTRL_BOTH 131 
#define  BNX2X_FLOW_CTRL_NONE 130 
#define  BNX2X_FLOW_CTRL_RX 129 
#define  BNX2X_FLOW_CTRL_TX 128 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_FULL_DUPLEX ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_NONE ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 

__attribute__((used)) static void bnx2x_calc_ieee_aneg_adv(struct bnx2x_phy *phy,
				     struct link_params *params, u16 *ieee_fc)
{
	struct bnx2x *bp = params->bp;
	*ieee_fc = MDIO_COMBO_IEEE0_AUTO_NEG_ADV_FULL_DUPLEX;
	/* Resolve pause mode and advertisement Please refer to Table
	 * 28B-3 of the 802.3ab-1999 spec
	 */

	switch (phy->req_flow_ctrl) {
	case BNX2X_FLOW_CTRL_AUTO:
		switch (params->req_fc_auto_adv) {
		case BNX2X_FLOW_CTRL_BOTH:
			*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH;
			break;
		case BNX2X_FLOW_CTRL_RX:
		case BNX2X_FLOW_CTRL_TX:
			*ieee_fc |=
				MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC;
			break;
		default:
			break;
		}
		break;
	case BNX2X_FLOW_CTRL_TX:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC;
		break;

	case BNX2X_FLOW_CTRL_RX:
	case BNX2X_FLOW_CTRL_BOTH:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH;
		break;

	case BNX2X_FLOW_CTRL_NONE:
	default:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_NONE;
		break;
	}
	DP(NETIF_MSG_LINK, "ieee_fc = 0x%x\n", *ieee_fc);
}