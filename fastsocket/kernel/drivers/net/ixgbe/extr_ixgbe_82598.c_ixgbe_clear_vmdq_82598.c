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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ num_rar_entries; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  IXGBE_RAH (scalar_t__) ; 
 scalar_t__ IXGBE_RAH_VIND_MASK ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,scalar_t__) ; 

__attribute__((used)) static s32 ixgbe_clear_vmdq_82598(struct ixgbe_hw *hw, u32 rar, u32 vmdq)
{
	u32 rar_high;
	u32 rar_entries = hw->mac.num_rar_entries;


	/* Make sure we are using a valid rar index range */
	if (rar >= rar_entries) {
		hw_dbg(hw, "RAR index %d is out of range.\n", rar);
		return IXGBE_ERR_INVALID_ARGUMENT;
	}

	rar_high = IXGBE_READ_REG(hw, IXGBE_RAH(rar));
	if (rar_high & IXGBE_RAH_VIND_MASK) {
		rar_high &= ~IXGBE_RAH_VIND_MASK;
		IXGBE_WRITE_REG(hw, IXGBE_RAH(rar), rar_high);
	}

	return 0;
}