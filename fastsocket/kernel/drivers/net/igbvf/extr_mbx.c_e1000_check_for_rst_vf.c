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
struct TYPE_3__ {int /*<<< orphan*/  rsts; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct e1000_hw {TYPE_2__ mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_MBX ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int E1000_V2PMAILBOX_RSTD ; 
 int E1000_V2PMAILBOX_RSTI ; 
 int /*<<< orphan*/  e1000_check_for_bit_vf (struct e1000_hw*,int) ; 

__attribute__((used)) static s32 e1000_check_for_rst_vf(struct e1000_hw *hw)
{
	s32 ret_val = -E1000_ERR_MBX;

	if (!e1000_check_for_bit_vf(hw, (E1000_V2PMAILBOX_RSTD |
	                                 E1000_V2PMAILBOX_RSTI))) {
		ret_val = E1000_SUCCESS;
		hw->mbx.stats.rsts++;
	}

	return ret_val;
}