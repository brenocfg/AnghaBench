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
struct e1000_hw {int mac_type; int /*<<< orphan*/  media_type; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int MII_CR_LOOPBACK ; 
 int /*<<< orphan*/  PHY_CTRL ; 
#define  e1000_82540 138 
#define  e1000_82541 137 
#define  e1000_82541_rev_2 136 
#define  e1000_82543 135 
#define  e1000_82544 134 
#define  e1000_82545 133 
#define  e1000_82545_rev_3 132 
#define  e1000_82546 131 
#define  e1000_82546_rev_3 130 
#define  e1000_82547 129 
#define  e1000_82547_rev_2 128 
 int e1000_integrated_phy_loopback (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_nonintegrated_phy_loopback (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int e1000_set_phy_loopback(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u16 phy_reg = 0;
	u16 count = 0;

	switch (hw->mac_type) {
	case e1000_82543:
		if (hw->media_type == e1000_media_type_copper) {
			/* Attempt to setup Loopback mode on Non-integrated PHY.
			 * Some PHY registers get corrupted at random, so
			 * attempt this 10 times.
			 */
			while (e1000_nonintegrated_phy_loopback(adapter) &&
			      count++ < 10);
			if (count < 11)
				return 0;
		}
		break;

	case e1000_82544:
	case e1000_82540:
	case e1000_82545:
	case e1000_82545_rev_3:
	case e1000_82546:
	case e1000_82546_rev_3:
	case e1000_82541:
	case e1000_82541_rev_2:
	case e1000_82547:
	case e1000_82547_rev_2:
		return e1000_integrated_phy_loopback(adapter);
		break;
	default:
		/* Default PHY loopback work is to read the MII
		 * control register and assert bit 14 (loopback mode).
		 */
		e1000_read_phy_reg(hw, PHY_CTRL, &phy_reg);
		phy_reg |= MII_CR_LOOPBACK;
		e1000_write_phy_reg(hw, PHY_CTRL, phy_reg);
		return 0;
		break;
	}

	return 8;
}