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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ vlan_id; } ;
struct TYPE_3__ {int type; } ;
struct e1000_hw {TYPE_2__ mng_cookie; TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_VFTA ; 
 int E1000_VFTA_ENTRY_BIT_SHIFT_MASK ; 
 scalar_t__ E1000_VFTA_ENTRY_MASK ; 
 scalar_t__ E1000_VFTA_ENTRY_SHIFT ; 
 scalar_t__ E1000_VLAN_FILTER_TBL_SIZE ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
#define  e1000_82573 130 
#define  e1000_82574 129 
#define  e1000_82583 128 
 int /*<<< orphan*/  e1e_flush () ; 

__attribute__((used)) static void e1000_clear_vfta_82571(struct e1000_hw *hw)
{
	u32 offset;
	u32 vfta_value = 0;
	u32 vfta_offset = 0;
	u32 vfta_bit_in_reg = 0;

	switch (hw->mac.type) {
	case e1000_82573:
	case e1000_82574:
	case e1000_82583:
		if (hw->mng_cookie.vlan_id != 0) {
			/* The VFTA is a 4096b bit-field, each identifying
			 * a single VLAN ID.  The following operations
			 * determine which 32b entry (i.e. offset) into the
			 * array we want to set the VLAN ID (i.e. bit) of
			 * the manageability unit.
			 */
			vfta_offset = (hw->mng_cookie.vlan_id >>
				       E1000_VFTA_ENTRY_SHIFT) &
			    E1000_VFTA_ENTRY_MASK;
			vfta_bit_in_reg =
			    1 << (hw->mng_cookie.vlan_id &
				  E1000_VFTA_ENTRY_BIT_SHIFT_MASK);
		}
		break;
	default:
		break;
	}
	for (offset = 0; offset < E1000_VLAN_FILTER_TBL_SIZE; offset++) {
		/* If the offset we want to clear is the same offset of the
		 * manageability VLAN ID, then clear all bits except that of
		 * the manageability unit.
		 */
		vfta_value = (offset == vfta_offset) ? vfta_bit_in_reg : 0;
		E1000_WRITE_REG_ARRAY(hw, E1000_VFTA, offset, vfta_value);
		e1e_flush();
	}
}