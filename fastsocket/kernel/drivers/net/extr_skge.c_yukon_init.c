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
struct skge_port {scalar_t__ autoneg; int advertising; size_t flow_control; scalar_t__ duplex; int speed; } ;
struct skge_hw {scalar_t__ copper; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  MAC_TX_CLK_25_MHZ ; 
 int PHY_AN_CSMA ; 
 int PHY_CT_ANE ; 
 int PHY_CT_DUP_MD ; 
 int PHY_CT_RESET ; 
 int PHY_CT_RE_CFG ; 
 int PHY_CT_SP100 ; 
 int PHY_CT_SP1000 ; 
 int /*<<< orphan*/  PHY_MARV_1000T_CTRL ; 
 int /*<<< orphan*/  PHY_MARV_AUNE_ADV ; 
 int /*<<< orphan*/  PHY_MARV_CTRL ; 
 int /*<<< orphan*/  PHY_MARV_EXT_CTRL ; 
 int /*<<< orphan*/  PHY_MARV_INT_MASK ; 
 int PHY_M_1000C_AFD ; 
 int PHY_M_1000C_AHD ; 
 int PHY_M_1000C_MSE ; 
 int PHY_M_AN_1000X_AFD ; 
 int PHY_M_AN_1000X_AHD ; 
 int PHY_M_AN_100_FD ; 
 int PHY_M_AN_100_HD ; 
 int PHY_M_AN_10_FD ; 
 int PHY_M_AN_10_HD ; 
 int PHY_M_EC_MAC_S (int /*<<< orphan*/ ) ; 
 int PHY_M_EC_MAC_S_MSK ; 
 int PHY_M_EC_M_DSC (int /*<<< orphan*/ ) ; 
 int PHY_M_EC_M_DSC_MSK ; 
 int PHY_M_EC_S_DSC (int) ; 
 int PHY_M_EC_S_DSC_MSK ; 
 int PHY_M_IS_AN_MSK ; 
 int PHY_M_IS_DEF_MSK ; 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int* fiber_pause_map ; 
 int gm_phy_read (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gm_phy_write (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 struct skge_port* netdev_priv (int /*<<< orphan*/ ) ; 
 int* phy_pause_map ; 

__attribute__((used)) static void yukon_init(struct skge_hw *hw, int port)
{
	struct skge_port *skge = netdev_priv(hw->dev[port]);
	u16 ctrl, ct1000, adv;

	if (skge->autoneg == AUTONEG_ENABLE) {
		u16 ectrl = gm_phy_read(hw, port, PHY_MARV_EXT_CTRL);

		ectrl &= ~(PHY_M_EC_M_DSC_MSK | PHY_M_EC_S_DSC_MSK |
			  PHY_M_EC_MAC_S_MSK);
		ectrl |= PHY_M_EC_MAC_S(MAC_TX_CLK_25_MHZ);

		ectrl |= PHY_M_EC_M_DSC(0) | PHY_M_EC_S_DSC(1);

		gm_phy_write(hw, port, PHY_MARV_EXT_CTRL, ectrl);
	}

	ctrl = gm_phy_read(hw, port, PHY_MARV_CTRL);
	if (skge->autoneg == AUTONEG_DISABLE)
		ctrl &= ~PHY_CT_ANE;

	ctrl |= PHY_CT_RESET;
	gm_phy_write(hw, port, PHY_MARV_CTRL, ctrl);

	ctrl = 0;
	ct1000 = 0;
	adv = PHY_AN_CSMA;

	if (skge->autoneg == AUTONEG_ENABLE) {
		if (hw->copper) {
			if (skge->advertising & ADVERTISED_1000baseT_Full)
				ct1000 |= PHY_M_1000C_AFD;
			if (skge->advertising & ADVERTISED_1000baseT_Half)
				ct1000 |= PHY_M_1000C_AHD;
			if (skge->advertising & ADVERTISED_100baseT_Full)
				adv |= PHY_M_AN_100_FD;
			if (skge->advertising & ADVERTISED_100baseT_Half)
				adv |= PHY_M_AN_100_HD;
			if (skge->advertising & ADVERTISED_10baseT_Full)
				adv |= PHY_M_AN_10_FD;
			if (skge->advertising & ADVERTISED_10baseT_Half)
				adv |= PHY_M_AN_10_HD;

			/* Set Flow-control capabilities */
			adv |= phy_pause_map[skge->flow_control];
		} else {
			if (skge->advertising & ADVERTISED_1000baseT_Full)
				adv |= PHY_M_AN_1000X_AFD;
			if (skge->advertising & ADVERTISED_1000baseT_Half)
				adv |= PHY_M_AN_1000X_AHD;

			adv |= fiber_pause_map[skge->flow_control];
		}

		/* Restart Auto-negotiation */
		ctrl |= PHY_CT_ANE | PHY_CT_RE_CFG;
	} else {
		/* forced speed/duplex settings */
		ct1000 = PHY_M_1000C_MSE;

		if (skge->duplex == DUPLEX_FULL)
			ctrl |= PHY_CT_DUP_MD;

		switch (skge->speed) {
		case SPEED_1000:
			ctrl |= PHY_CT_SP1000;
			break;
		case SPEED_100:
			ctrl |= PHY_CT_SP100;
			break;
		}

		ctrl |= PHY_CT_RESET;
	}

	gm_phy_write(hw, port, PHY_MARV_1000T_CTRL, ct1000);

	gm_phy_write(hw, port, PHY_MARV_AUNE_ADV, adv);
	gm_phy_write(hw, port, PHY_MARV_CTRL, ctrl);

	/* Enable phy interrupt on autonegotiation complete (or link up) */
	if (skge->autoneg == AUTONEG_ENABLE)
		gm_phy_write(hw, port, PHY_MARV_INT_MASK, PHY_M_IS_AN_MSK);
	else
		gm_phy_write(hw, port, PHY_MARV_INT_MASK, PHY_M_IS_DEF_MSK);
}