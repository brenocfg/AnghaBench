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
struct atl1_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ atl1_write_phy_reg (struct atl1_hw*,int,int) ; 

__attribute__((used)) static s32 atl1_phy_leave_power_saving(struct atl1_hw *hw)
{
	s32 ret;
	ret = atl1_write_phy_reg(hw, 29, 0x0029);
	if (ret)
		return ret;
	return atl1_write_phy_reg(hw, 30, 0);
}