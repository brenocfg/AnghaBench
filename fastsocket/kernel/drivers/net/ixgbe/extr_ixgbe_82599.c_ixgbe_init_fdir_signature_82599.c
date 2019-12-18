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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int IXGBE_FDIRCTRL_FLEX_SHIFT ; 
 int IXGBE_FDIRCTRL_FULL_THRESH_SHIFT ; 
 int IXGBE_FDIRCTRL_MAX_LENGTH_SHIFT ; 
 int /*<<< orphan*/  ixgbe_fdir_enable_82599 (struct ixgbe_hw*,int) ; 

s32 ixgbe_init_fdir_signature_82599(struct ixgbe_hw *hw, u32 fdirctrl)
{
	/*
	 * Continue setup of fdirctrl register bits:
	 *  Move the flexible bytes to use the ethertype - shift 6 words
	 *  Set the maximum length per hash bucket to 0xA filters
	 *  Send interrupt when 64 filters are left
	 */
	fdirctrl |= (0x6 << IXGBE_FDIRCTRL_FLEX_SHIFT) |
		    (0xA << IXGBE_FDIRCTRL_MAX_LENGTH_SHIFT) |
		    (4 << IXGBE_FDIRCTRL_FULL_THRESH_SHIFT);

	/* write hashes and fdirctrl register, poll for completion */
	ixgbe_fdir_enable_82599(hw, fdirctrl);

	return 0;
}