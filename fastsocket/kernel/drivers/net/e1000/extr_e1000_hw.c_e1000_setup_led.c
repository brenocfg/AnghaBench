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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int mac_type; int phy_spd_default; int ledctl_default; int ledctl_mode1; int /*<<< orphan*/  media_type; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int E1000_LEDCTL_LED0_BLINK ; 
 int E1000_LEDCTL_LED0_IVRT ; 
 int E1000_LEDCTL_LED0_MODE_MASK ; 
 int E1000_LEDCTL_LED0_MODE_SHIFT ; 
 int E1000_LEDCTL_MODE_LED_OFF ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  IGP01E1000_GMII_FIFO ; 
 int IGP01E1000_GMII_SPD ; 
 int /*<<< orphan*/  LEDCTL ; 
#define  e1000_82541 135 
#define  e1000_82541_rev_2 134 
#define  e1000_82542_rev2_0 133 
#define  e1000_82542_rev2_1 132 
#define  e1000_82543 131 
#define  e1000_82544 130 
#define  e1000_82547 129 
#define  e1000_82547_rev_2 128 
 int /*<<< orphan*/  e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_media_type_fiber ; 
 int /*<<< orphan*/  e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

s32 e1000_setup_led(struct e1000_hw *hw)
{
	u32 ledctl;
	s32 ret_val = E1000_SUCCESS;

	e_dbg("e1000_setup_led");

	switch (hw->mac_type) {
	case e1000_82542_rev2_0:
	case e1000_82542_rev2_1:
	case e1000_82543:
	case e1000_82544:
		/* No setup necessary */
		break;
	case e1000_82541:
	case e1000_82547:
	case e1000_82541_rev_2:
	case e1000_82547_rev_2:
		/* Turn off PHY Smart Power Down (if enabled) */
		ret_val = e1000_read_phy_reg(hw, IGP01E1000_GMII_FIFO,
					     &hw->phy_spd_default);
		if (ret_val)
			return ret_val;
		ret_val = e1000_write_phy_reg(hw, IGP01E1000_GMII_FIFO,
					      (u16) (hw->phy_spd_default &
						     ~IGP01E1000_GMII_SPD));
		if (ret_val)
			return ret_val;
		/* Fall Through */
	default:
		if (hw->media_type == e1000_media_type_fiber) {
			ledctl = er32(LEDCTL);
			/* Save current LEDCTL settings */
			hw->ledctl_default = ledctl;
			/* Turn off LED0 */
			ledctl &= ~(E1000_LEDCTL_LED0_IVRT |
				    E1000_LEDCTL_LED0_BLINK |
				    E1000_LEDCTL_LED0_MODE_MASK);
			ledctl |= (E1000_LEDCTL_MODE_LED_OFF <<
				   E1000_LEDCTL_LED0_MODE_SHIFT);
			ew32(LEDCTL, ledctl);
		} else if (hw->media_type == e1000_media_type_copper)
			ew32(LEDCTL, hw->ledctl_mode1);
		break;
	}

	return E1000_SUCCESS;
}