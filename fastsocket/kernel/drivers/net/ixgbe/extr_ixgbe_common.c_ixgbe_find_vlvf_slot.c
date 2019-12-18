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
struct ixgbe_hw {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int IXGBE_ERR_NO_SPACE ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VLVF (int) ; 
 int IXGBE_VLVF_ENTRIES ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 

__attribute__((used)) static s32 ixgbe_find_vlvf_slot(struct ixgbe_hw *hw, u32 vlan)
{
	u32 bits = 0;
	u32 first_empty_slot = 0;
	s32 regindex;

	/* short cut the special case */
	if (vlan == 0)
		return 0;

	/*
	  * Search for the vlan id in the VLVF entries. Save off the first empty
	  * slot found along the way
	  */
	for (regindex = 1; regindex < IXGBE_VLVF_ENTRIES; regindex++) {
		bits = IXGBE_READ_REG(hw, IXGBE_VLVF(regindex));
		if (!bits && !(first_empty_slot))
			first_empty_slot = regindex;
		else if ((bits & 0x0FFF) == vlan)
			break;
	}

	/*
	  * If regindex is less than IXGBE_VLVF_ENTRIES, then we found the vlan
	  * in the VLVF. Else use the first empty VLVF register for this
	  * vlan id.
	  */
	if (regindex >= IXGBE_VLVF_ENTRIES) {
		if (first_empty_slot)
			regindex = first_empty_slot;
		else {
			hw_dbg(hw, "No space in VLVF.\n");
			regindex = IXGBE_ERR_NO_SPACE;
		}
	}

	return regindex;
}