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
struct sky2_hw {scalar_t__ chip_id; scalar_t__ chip_rev; struct net_device** dev; } ;
struct net_device {scalar_t__ mtu; int features; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_YUKON_EX ; 
 scalar_t__ CHIP_ID_YUKON_FE_P ; 
 scalar_t__ CHIP_ID_YUKON_SUPR ; 
 scalar_t__ CHIP_REV_YU_EX_A0 ; 
 int ECU_AE_THR ; 
 int ECU_JUMBO_WM ; 
 scalar_t__ ETH_DATA_LEN ; 
 int NETIF_F_ALL_CSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_GMF_AE_THR ; 
 int /*<<< orphan*/  TX_GMF_CTRL_T ; 
 int TX_JUMBO_DIS ; 
 int TX_JUMBO_ENA ; 
 int TX_STFW_DIS ; 
 int TX_STFW_ENA ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sky2_set_tx_stfwd(struct sky2_hw *hw, unsigned port)
{
	struct net_device *dev = hw->dev[port];

	if ( (hw->chip_id == CHIP_ID_YUKON_EX &&
	      hw->chip_rev != CHIP_REV_YU_EX_A0) ||
	     hw->chip_id == CHIP_ID_YUKON_FE_P ||
	     hw->chip_id == CHIP_ID_YUKON_SUPR) {
		/* Yukon-Extreme B0 and further Extreme devices */
		/* enable Store & Forward mode for TX */

		if (dev->mtu <= ETH_DATA_LEN)
			sky2_write32(hw, SK_REG(port, TX_GMF_CTRL_T),
				     TX_JUMBO_DIS | TX_STFW_ENA);

		else
			sky2_write32(hw, SK_REG(port, TX_GMF_CTRL_T),
				     TX_JUMBO_ENA| TX_STFW_ENA);
	} else {
		if (dev->mtu <= ETH_DATA_LEN)
			sky2_write32(hw, SK_REG(port, TX_GMF_CTRL_T), TX_STFW_ENA);
		else {
			/* set Tx GMAC FIFO Almost Empty Threshold */
			sky2_write32(hw, SK_REG(port, TX_GMF_AE_THR),
				     (ECU_JUMBO_WM << 16) | ECU_AE_THR);

			sky2_write32(hw, SK_REG(port, TX_GMF_CTRL_T), TX_STFW_DIS);

			/* Can't do offload because of lack of store/forward */
			dev->features &= ~(NETIF_F_TSO | NETIF_F_SG | NETIF_F_ALL_CSUM);
		}
	}
}