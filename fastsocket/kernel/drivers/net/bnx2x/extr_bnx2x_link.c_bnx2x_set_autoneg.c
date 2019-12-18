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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct link_vars {scalar_t__ line_speed; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int speed_cap_mask; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL ; 
 int MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_BAM_MODE ; 
 int MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_TETON_AN ; 
 int /*<<< orphan*/  MDIO_CL73_IEEEB0_CL73_AN_CONTROL ; 
 int MDIO_CL73_IEEEB0_CL73_AN_CONTROL_AN_EN ; 
 int /*<<< orphan*/  MDIO_CL73_IEEEB1_AN_ADV2 ; 
 int MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX ; 
 int MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4 ; 
 int /*<<< orphan*/  MDIO_CL73_USERB0_CL73_BAM_CTRL1 ; 
 int MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_EN ; 
 int MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_NP_AFTER_BP_EN ; 
 int MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_STATION_MNGR_EN ; 
 int /*<<< orphan*/  MDIO_CL73_USERB0_CL73_UCTRL ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_MII_CONTROL ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_AN_EN ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_RESTART_AN ; 
 int /*<<< orphan*/  MDIO_REG_BANK_BAM_NEXT_PAGE ; 
 int /*<<< orphan*/  MDIO_REG_BANK_CL73_IEEEB0 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_CL73_IEEEB1 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_CL73_USERB0 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_COMBO_IEEE0 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_SERDES_DIGITAL ; 
 int /*<<< orphan*/  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1 ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_AUTODET ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_FIBER_MODE ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_INVERT_SIGNAL_DETECT ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_SIGNAL_DETECT_EN ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10G ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_1G ; 
 scalar_t__ SPEED_AUTO_NEG ; 

__attribute__((used)) static void bnx2x_set_autoneg(struct bnx2x_phy *phy,
			      struct link_params *params,
			      struct link_vars *vars,
			      u8 enable_cl73)
{
	struct bnx2x *bp = params->bp;
	u16 reg_val;

	/* CL37 Autoneg */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL, &reg_val);

	/* CL37 Autoneg Enabled */
	if (vars->line_speed == SPEED_AUTO_NEG)
		reg_val |= MDIO_COMBO_IEEO_MII_CONTROL_AN_EN;
	else /* CL37 Autoneg Disabled */
		reg_val &= ~(MDIO_COMBO_IEEO_MII_CONTROL_AN_EN |
			     MDIO_COMBO_IEEO_MII_CONTROL_RESTART_AN);

	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL, reg_val);

	/* Enable/Disable Autodetection */

	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1, &reg_val);
	reg_val &= ~(MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_SIGNAL_DETECT_EN |
		    MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_INVERT_SIGNAL_DETECT);
	reg_val |= MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_FIBER_MODE;
	if (vars->line_speed == SPEED_AUTO_NEG)
		reg_val |= MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_AUTODET;
	else
		reg_val &= ~MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_AUTODET;

	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1, reg_val);

	/* Enable TetonII and BAM autoneg */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_BAM_NEXT_PAGE,
			  MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL,
			  &reg_val);
	if (vars->line_speed == SPEED_AUTO_NEG) {
		/* Enable BAM aneg Mode and TetonII aneg Mode */
		reg_val |= (MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_BAM_MODE |
			    MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_TETON_AN);
	} else {
		/* TetonII and BAM Autoneg Disabled */
		reg_val &= ~(MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_BAM_MODE |
			     MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_TETON_AN);
	}
	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_BAM_NEXT_PAGE,
			  MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL,
			  reg_val);

	if (enable_cl73) {
		/* Enable Cl73 FSM status bits */
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_USERB0,
				  MDIO_CL73_USERB0_CL73_UCTRL,
				  0xe);

		/* Enable BAM Station Manager*/
		CL22_WR_OVER_CL45(bp, phy,
			MDIO_REG_BANK_CL73_USERB0,
			MDIO_CL73_USERB0_CL73_BAM_CTRL1,
			MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_EN |
			MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_STATION_MNGR_EN |
			MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_NP_AFTER_BP_EN);

		/* Advertise CL73 link speeds */
		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_ADV2,
				  &reg_val);
		if (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)
			reg_val |= MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4;
		if (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)
			reg_val |= MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX;

		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_ADV2,
				  reg_val);

		/* CL73 Autoneg Enabled */
		reg_val = MDIO_CL73_IEEEB0_CL73_AN_CONTROL_AN_EN;

	} else /* CL73 Autoneg Disabled */
		reg_val = 0;

	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_CL73_IEEEB0,
			  MDIO_CL73_IEEEB0_CL73_AN_CONTROL, reg_val);
}