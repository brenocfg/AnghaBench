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
typedef  int u32 ;
struct igb_adapter {int* shadow_vfta; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; struct igb_adapter* back; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_CONFIG ; 
 int E1000_VFTA_ENTRY_BIT_SHIFT_MASK ; 
 int E1000_VFTA_ENTRY_MASK ; 
 int E1000_VFTA_ENTRY_SHIFT ; 
 scalar_t__ e1000_i350 ; 
 scalar_t__ e1000_i354 ; 
 int /*<<< orphan*/  igb_write_vfta (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  igb_write_vfta_i350 (struct e1000_hw*,int,int) ; 

s32 igb_vfta_set(struct e1000_hw *hw, u32 vid, bool add)
{
	u32 index = (vid >> E1000_VFTA_ENTRY_SHIFT) & E1000_VFTA_ENTRY_MASK;
	u32 mask = 1 << (vid & E1000_VFTA_ENTRY_BIT_SHIFT_MASK);
	u32 vfta;
	struct igb_adapter *adapter = hw->back;
	s32 ret_val = 0;

	vfta = adapter->shadow_vfta[index];

	/* bit was set/cleared before we started */
	if ((!!(vfta & mask)) == add) {
		ret_val = -E1000_ERR_CONFIG;
	} else {
		if (add)
			vfta |= mask;
		else
			vfta &= ~mask;
	}
	if ((hw->mac.type == e1000_i350) || (hw->mac.type == e1000_i354))
		igb_write_vfta_i350(hw, index, vfta);
	else
		igb_write_vfta(hw, index, vfta);
	adapter->shadow_vfta[index] = vfta;

	return ret_val;
}