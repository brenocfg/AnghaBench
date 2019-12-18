#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int original_ms_type; int ms_type; } ;
struct e1000_hw {TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int CTL1000_AS_MASTER ; 
 int CTL1000_ENABLE_MASTER ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
#define  e1000_ms_auto 130 
#define  e1000_ms_force_master 129 
#define  e1000_ms_force_slave 128 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_set_master_slave_mode(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 phy_data;

	/* Resolve Master/Slave mode */
	ret_val = e1e_rphy(hw, MII_CTRL1000, &phy_data);
	if (ret_val)
		return ret_val;

	/* load defaults for future use */
	hw->phy.original_ms_type = (phy_data & CTL1000_ENABLE_MASTER) ?
	    ((phy_data & CTL1000_AS_MASTER) ?
	     e1000_ms_force_master : e1000_ms_force_slave) : e1000_ms_auto;

	switch (hw->phy.ms_type) {
	case e1000_ms_force_master:
		phy_data |= (CTL1000_ENABLE_MASTER | CTL1000_AS_MASTER);
		break;
	case e1000_ms_force_slave:
		phy_data |= CTL1000_ENABLE_MASTER;
		phy_data &= ~(CTL1000_AS_MASTER);
		break;
	case e1000_ms_auto:
		phy_data &= ~CTL1000_ENABLE_MASTER;
		/* fall-through */
	default:
		break;
	}

	return e1e_wphy(hw, MII_CTRL1000, phy_data);
}