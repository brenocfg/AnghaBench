#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* commit ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; int /*<<< orphan*/  type; int /*<<< orphan*/  media_type; } ;
struct TYPE_4__ {int type; int autoneg; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
struct e1000_adapter {int tx_fifo_head; struct e1000_hw hw; } ;

/* Variables and functions */
 int BMCR_LOOPBACK ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_RCTL_LBM_MAC ; 
 int E1000_RCTL_LBM_TCVR ; 
 int E1000_SCTL_DISABLE_SERDES_LOOPBACK ; 
 int /*<<< orphan*/  GG82563_PHY_KMRN_MODE_CTRL ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  SCTL ; 
#define  e1000_80003es2lan 130 
#define  e1000_82571 129 
#define  e1000_82572 128 
 int /*<<< orphan*/  e1000_media_type_fiber ; 
 int /*<<< orphan*/  e1000_media_type_internal_serdes ; 
 int /*<<< orphan*/  e1000_phy_gg82563 ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void e1000_loopback_cleanup(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 rctl;
	u16 phy_reg;

	rctl = er32(RCTL);
	rctl &= ~(E1000_RCTL_LBM_TCVR | E1000_RCTL_LBM_MAC);
	ew32(RCTL, rctl);

	switch (hw->mac.type) {
	case e1000_80003es2lan:
		if (hw->phy.media_type == e1000_media_type_fiber ||
		    hw->phy.media_type == e1000_media_type_internal_serdes) {
			/* restore CTRL_EXT, stealing space from tx_fifo_head */
			ew32(CTRL_EXT, adapter->tx_fifo_head);
			adapter->tx_fifo_head = 0;
		}
		/* fall through */
	case e1000_82571:
	case e1000_82572:
		if (hw->phy.media_type == e1000_media_type_fiber ||
		    hw->phy.media_type == e1000_media_type_internal_serdes) {
			ew32(SCTL, E1000_SCTL_DISABLE_SERDES_LOOPBACK);
			e1e_flush();
			usleep_range(10000, 20000);
			break;
		}
		/* Fall Through */
	default:
		hw->mac.autoneg = 1;
		if (hw->phy.type == e1000_phy_gg82563)
			e1e_wphy(hw, GG82563_PHY_KMRN_MODE_CTRL, 0x180);
		e1e_rphy(hw, MII_BMCR, &phy_reg);
		if (phy_reg & BMCR_LOOPBACK) {
			phy_reg &= ~BMCR_LOOPBACK;
			e1e_wphy(hw, MII_BMCR, phy_reg);
			if (hw->phy.ops.commit)
				hw->phy.ops.commit(hw);
		}
		break;
	}
}