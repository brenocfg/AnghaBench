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
struct TYPE_3__ {scalar_t__ (* reset_hw ) (struct ixgbe_hw*) ;scalar_t__ (* start_hw ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*) ; 

s32 ixgbe_init_hw_generic(struct ixgbe_hw *hw)
{
	s32 status;

	/* Reset the hardware */
	status = hw->mac.ops.reset_hw(hw);

	if (status == 0) {
		/* Start the HW */
		status = hw->mac.ops.start_hw(hw);
	}

	return status;
}