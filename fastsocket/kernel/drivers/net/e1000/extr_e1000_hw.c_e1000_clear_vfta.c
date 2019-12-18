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
typedef  scalar_t__ u32 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ E1000_VLAN_FILTER_TBL_SIZE ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VFTA ; 

__attribute__((used)) static void e1000_clear_vfta(struct e1000_hw *hw)
{
	u32 offset;
	u32 vfta_value = 0;
	u32 vfta_offset = 0;
	u32 vfta_bit_in_reg = 0;

	for (offset = 0; offset < E1000_VLAN_FILTER_TBL_SIZE; offset++) {
		/* If the offset we want to clear is the same offset of the
		 * manageability VLAN ID, then clear all bits except that of the
		 * manageability unit */
		vfta_value = (offset == vfta_offset) ? vfta_bit_in_reg : 0;
		E1000_WRITE_REG_ARRAY(hw, VFTA, offset, vfta_value);
		E1000_WRITE_FLUSH();
	}
}