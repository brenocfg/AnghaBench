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
struct e1000_hw {int mac_type; int /*<<< orphan*/  ledctl_default; int /*<<< orphan*/  phy_spd_default; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  IGP01E1000_GMII_FIFO ; 
 int /*<<< orphan*/  LEDCTL ; 
#define  e1000_82541 135 
#define  e1000_82541_rev_2 134 
#define  e1000_82542_rev2_0 133 
#define  e1000_82542_rev2_1 132 
#define  e1000_82543 131 
#define  e1000_82544 130 
#define  e1000_82547 129 
#define  e1000_82547_rev_2 128 
 int /*<<< orphan*/  e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 e1000_cleanup_led(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;

	e_dbg("e1000_cleanup_led");

	switch (hw->mac_type) {
	case e1000_82542_rev2_0:
	case e1000_82542_rev2_1:
	case e1000_82543:
	case e1000_82544:
		/* No cleanup necessary */
		break;
	case e1000_82541:
	case e1000_82547:
	case e1000_82541_rev_2:
	case e1000_82547_rev_2:
		/* Turn on PHY Smart Power Down (if previously enabled) */
		ret_val = e1000_write_phy_reg(hw, IGP01E1000_GMII_FIFO,
					      hw->phy_spd_default);
		if (ret_val)
			return ret_val;
		/* Fall Through */
	default:
		/* Restore LEDCTL settings */
		ew32(LEDCTL, hw->ledctl_default);
		break;
	}

	return E1000_SUCCESS;
}