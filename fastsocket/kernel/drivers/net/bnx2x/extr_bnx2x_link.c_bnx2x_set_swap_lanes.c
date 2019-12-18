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
struct link_params {int lane_config; struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MDIO_REG_BANK_XGXS_BLOCK2 ; 
 int /*<<< orphan*/  MDIO_XGXS_BLOCK2_RX_LN_SWAP ; 
 int MDIO_XGXS_BLOCK2_RX_LN_SWAP_ENABLE ; 
 int MDIO_XGXS_BLOCK2_RX_LN_SWAP_FORCE_ENABLE ; 
 int /*<<< orphan*/  MDIO_XGXS_BLOCK2_TX_LN_SWAP ; 
 int MDIO_XGXS_BLOCK2_TX_LN_SWAP_ENABLE ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_RX_MASK ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_RX_SHIFT ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_TX_MASK ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_TX_SHIFT ; 

__attribute__((used)) static void bnx2x_set_swap_lanes(struct link_params *params,
				 struct bnx2x_phy *phy)
{
	struct bnx2x *bp = params->bp;
	/* Each two bits represents a lane number:
	 * No swap is 0123 => 0x1b no need to enable the swap
	 */
	u16 rx_lane_swap, tx_lane_swap;

	rx_lane_swap = ((params->lane_config &
			 PORT_HW_CFG_LANE_SWAP_CFG_RX_MASK) >>
			PORT_HW_CFG_LANE_SWAP_CFG_RX_SHIFT);
	tx_lane_swap = ((params->lane_config &
			 PORT_HW_CFG_LANE_SWAP_CFG_TX_MASK) >>
			PORT_HW_CFG_LANE_SWAP_CFG_TX_SHIFT);

	if (rx_lane_swap != 0x1b) {
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_XGXS_BLOCK2,
				  MDIO_XGXS_BLOCK2_RX_LN_SWAP,
				  (rx_lane_swap |
				   MDIO_XGXS_BLOCK2_RX_LN_SWAP_ENABLE |
				   MDIO_XGXS_BLOCK2_RX_LN_SWAP_FORCE_ENABLE));
	} else {
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_XGXS_BLOCK2,
				  MDIO_XGXS_BLOCK2_RX_LN_SWAP, 0);
	}

	if (tx_lane_swap != 0x1b) {
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_XGXS_BLOCK2,
				  MDIO_XGXS_BLOCK2_TX_LN_SWAP,
				  (tx_lane_swap |
				   MDIO_XGXS_BLOCK2_TX_LN_SWAP_ENABLE));
	} else {
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_XGXS_BLOCK2,
				  MDIO_XGXS_BLOCK2_TX_LN_SWAP, 0);
	}
}