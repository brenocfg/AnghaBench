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
struct skge_port {int port; scalar_t__ autoneg; int advertising; size_t flow_control; scalar_t__ duplex; int /*<<< orphan*/  link_timer; struct skge_hw* hw; } ;
struct skge_hw {int dummy; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ LINK_HZ ; 
 int PHY_CT_ANE ; 
 int PHY_CT_DUP_MD ; 
 int PHY_CT_RE_CFG ; 
 int /*<<< orphan*/  PHY_XMAC_AUNE_ADV ; 
 int /*<<< orphan*/  PHY_XMAC_CTRL ; 
 int PHY_X_AN_FD ; 
 int PHY_X_AN_HD ; 
 int* fiber_pause_map ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xm_phy_write (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xm_phy_init(struct skge_port *skge)
{
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	u16 ctrl = 0;

	if (skge->autoneg == AUTONEG_ENABLE) {
		if (skge->advertising & ADVERTISED_1000baseT_Half)
			ctrl |= PHY_X_AN_HD;
		if (skge->advertising & ADVERTISED_1000baseT_Full)
			ctrl |= PHY_X_AN_FD;

		ctrl |= fiber_pause_map[skge->flow_control];

		xm_phy_write(hw, port, PHY_XMAC_AUNE_ADV, ctrl);

		/* Restart Auto-negotiation */
		ctrl = PHY_CT_ANE | PHY_CT_RE_CFG;
	} else {
		/* Set DuplexMode in Config register */
		if (skge->duplex == DUPLEX_FULL)
			ctrl |= PHY_CT_DUP_MD;
		/*
		 * Do NOT enable Auto-negotiation here. This would hold
		 * the link down because no IDLEs are transmitted
		 */
	}

	xm_phy_write(hw, port, PHY_XMAC_CTRL, ctrl);

	/* Poll PHY for status changes */
	mod_timer(&skge->link_timer, jiffies + LINK_HZ);
}