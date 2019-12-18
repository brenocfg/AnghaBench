#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_analog_reg8 ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_analog_reg8 ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {scalar_t__ type; int orig_autoc; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_10G ; 
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_1G ; 
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_AN ; 
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_LPBK ; 
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_TX_10G_QL_ALL ; 
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_TX_1G_QL_ALL ; 
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_TX_AN_QL_ALL ; 
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_TX_REG_EN ; 
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 int IXGBE_AUTOC_FLU ; 
 int /*<<< orphan*/  IXGBE_FCTRL ; 
 int IXGBE_FCTRL_BAM ; 
 int IXGBE_FCTRL_MPE ; 
 int IXGBE_FCTRL_SBP ; 
 int /*<<< orphan*/  IXGBE_HLREG0 ; 
 int IXGBE_HLREG0_LPBK ; 
 int /*<<< orphan*/  IXGBE_MACC ; 
 int IXGBE_MACC_FLU ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 scalar_t__ ixgbe_mac_X540 ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ixgbe_setup_loopback_test(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 reg_data;


	/* Setup MAC loopback */
	reg_data = IXGBE_READ_REG(hw, IXGBE_HLREG0);
	reg_data |= IXGBE_HLREG0_LPBK;
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, reg_data);

	reg_data = IXGBE_READ_REG(hw, IXGBE_FCTRL);
	reg_data |= IXGBE_FCTRL_BAM | IXGBE_FCTRL_SBP | IXGBE_FCTRL_MPE;
	IXGBE_WRITE_REG(hw, IXGBE_FCTRL, reg_data);

	/* X540 needs to set the MACC.FLU bit to force link up */
	if (adapter->hw.mac.type == ixgbe_mac_X540) {
		reg_data = IXGBE_READ_REG(hw, IXGBE_MACC);
		reg_data |= IXGBE_MACC_FLU;
		IXGBE_WRITE_REG(hw, IXGBE_MACC, reg_data);
	} else {
		if (hw->mac.orig_autoc) {
			reg_data = hw->mac.orig_autoc | IXGBE_AUTOC_FLU;
			IXGBE_WRITE_REG(hw, IXGBE_AUTOC, reg_data);
		} else {
			return 10;
		}
	}
	IXGBE_WRITE_FLUSH(hw);
	usleep_range(10000, 20000);

	/* Disable Atlas Tx lanes; re-enabled in reset path */
	if (hw->mac.type == ixgbe_mac_82598EB) {
		u8 atlas;

		hw->mac.ops.read_analog_reg8(hw, IXGBE_ATLAS_PDN_LPBK, &atlas);
		atlas |= IXGBE_ATLAS_PDN_TX_REG_EN;
		hw->mac.ops.write_analog_reg8(hw, IXGBE_ATLAS_PDN_LPBK, atlas);

		hw->mac.ops.read_analog_reg8(hw, IXGBE_ATLAS_PDN_10G, &atlas);
		atlas |= IXGBE_ATLAS_PDN_TX_10G_QL_ALL;
		hw->mac.ops.write_analog_reg8(hw, IXGBE_ATLAS_PDN_10G, atlas);

		hw->mac.ops.read_analog_reg8(hw, IXGBE_ATLAS_PDN_1G, &atlas);
		atlas |= IXGBE_ATLAS_PDN_TX_1G_QL_ALL;
		hw->mac.ops.write_analog_reg8(hw, IXGBE_ATLAS_PDN_1G, atlas);

		hw->mac.ops.read_analog_reg8(hw, IXGBE_ATLAS_PDN_AN, &atlas);
		atlas |= IXGBE_ATLAS_PDN_TX_AN_QL_ALL;
		hw->mac.ops.write_analog_reg8(hw, IXGBE_ATLAS_PDN_AN, atlas);
	}

	return 0;
}