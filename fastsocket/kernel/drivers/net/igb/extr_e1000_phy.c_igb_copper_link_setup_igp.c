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
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;scalar_t__ (* set_d0_lplu_state ) (struct e1000_hw*,int) ;scalar_t__ (* set_d3_lplu_state ) (struct e1000_hw*,int) ;scalar_t__ (* reset ) (struct e1000_hw*) ;} ;
struct e1000_phy_info {scalar_t__ type; int mdix; scalar_t__ autoneg_advertised; int original_ms_type; int ms_type; TYPE_2__ ops; scalar_t__ reset_disable; } ;
struct TYPE_3__ {scalar_t__ autoneg; } ;
struct e1000_hw {TYPE_1__ mac; struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ ADVERTISE_1000_FULL ; 
 int CR_1000T_MS_ENABLE ; 
 int CR_1000T_MS_VALUE ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_CONFIG ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_CTRL ; 
 int IGP01E1000_PSCFR_SMART_SPEED ; 
 int IGP01E1000_PSCR_AUTO_MDIX ; 
 int IGP01E1000_PSCR_FORCE_MDI_MDIX ; 
 int /*<<< orphan*/  PHY_1000T_CTRL ; 
#define  e1000_ms_auto 130 
#define  e1000_ms_force_master 129 
#define  e1000_ms_force_slave 128 
 scalar_t__ e1000_phy_igp ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 scalar_t__ stub10 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub11 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (struct e1000_hw*,int) ; 
 scalar_t__ stub3 (struct e1000_hw*,int) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub7 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub8 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub9 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

s32 igb_copper_link_setup_igp(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	if (phy->reset_disable) {
		ret_val = 0;
		goto out;
	}

	ret_val = phy->ops.reset(hw);
	if (ret_val) {
		hw_dbg("Error resetting the PHY.\n");
		goto out;
	}

	/* Wait 100ms for MAC to configure PHY from NVM settings, to avoid
	 * timeout issues when LFS is enabled.
	 */
	msleep(100);

	/* The NVM settings will configure LPLU in D3 for
	 * non-IGP1 PHYs.
	 */
	if (phy->type == e1000_phy_igp) {
		/* disable lplu d3 during driver init */
		if (phy->ops.set_d3_lplu_state)
			ret_val = phy->ops.set_d3_lplu_state(hw, false);
		if (ret_val) {
			hw_dbg("Error Disabling LPLU D3\n");
			goto out;
		}
	}

	/* disable lplu d0 during driver init */
	ret_val = phy->ops.set_d0_lplu_state(hw, false);
	if (ret_val) {
		hw_dbg("Error Disabling LPLU D0\n");
		goto out;
	}
	/* Configure mdi-mdix settings */
	ret_val = phy->ops.read_reg(hw, IGP01E1000_PHY_PORT_CTRL, &data);
	if (ret_val)
		goto out;

	data &= ~IGP01E1000_PSCR_AUTO_MDIX;

	switch (phy->mdix) {
	case 1:
		data &= ~IGP01E1000_PSCR_FORCE_MDI_MDIX;
		break;
	case 2:
		data |= IGP01E1000_PSCR_FORCE_MDI_MDIX;
		break;
	case 0:
	default:
		data |= IGP01E1000_PSCR_AUTO_MDIX;
		break;
	}
	ret_val = phy->ops.write_reg(hw, IGP01E1000_PHY_PORT_CTRL, data);
	if (ret_val)
		goto out;

	/* set auto-master slave resolution settings */
	if (hw->mac.autoneg) {
		/* when autonegotiation advertisement is only 1000Mbps then we
		 * should disable SmartSpeed and enable Auto MasterSlave
		 * resolution as hardware default.
		 */
		if (phy->autoneg_advertised == ADVERTISE_1000_FULL) {
			/* Disable SmartSpeed */
			ret_val = phy->ops.read_reg(hw,
						    IGP01E1000_PHY_PORT_CONFIG,
						    &data);
			if (ret_val)
				goto out;

			data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.write_reg(hw,
						     IGP01E1000_PHY_PORT_CONFIG,
						     data);
			if (ret_val)
				goto out;

			/* Set auto Master/Slave resolution process */
			ret_val = phy->ops.read_reg(hw, PHY_1000T_CTRL, &data);
			if (ret_val)
				goto out;

			data &= ~CR_1000T_MS_ENABLE;
			ret_val = phy->ops.write_reg(hw, PHY_1000T_CTRL, data);
			if (ret_val)
				goto out;
		}

		ret_val = phy->ops.read_reg(hw, PHY_1000T_CTRL, &data);
		if (ret_val)
			goto out;

		/* load defaults for future use */
		phy->original_ms_type = (data & CR_1000T_MS_ENABLE) ?
			((data & CR_1000T_MS_VALUE) ?
			e1000_ms_force_master :
			e1000_ms_force_slave) :
			e1000_ms_auto;

		switch (phy->ms_type) {
		case e1000_ms_force_master:
			data |= (CR_1000T_MS_ENABLE | CR_1000T_MS_VALUE);
			break;
		case e1000_ms_force_slave:
			data |= CR_1000T_MS_ENABLE;
			data &= ~(CR_1000T_MS_VALUE);
			break;
		case e1000_ms_auto:
			data &= ~CR_1000T_MS_ENABLE;
		default:
			break;
		}
		ret_val = phy->ops.write_reg(hw, PHY_1000T_CTRL, data);
		if (ret_val)
			goto out;
	}

out:
	return ret_val;
}