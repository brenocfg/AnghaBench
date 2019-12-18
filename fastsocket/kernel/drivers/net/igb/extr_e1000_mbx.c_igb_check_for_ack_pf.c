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
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  acks; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct e1000_hw {TYPE_2__ mbx; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_MBX ; 
 int E1000_MBVFICR_VFACK_VF1 ; 
 int /*<<< orphan*/  igb_check_for_bit_pf (struct e1000_hw*,int) ; 

__attribute__((used)) static s32 igb_check_for_ack_pf(struct e1000_hw *hw, u16 vf_number)
{
	s32 ret_val = -E1000_ERR_MBX;

	if (!igb_check_for_bit_pf(hw, E1000_MBVFICR_VFACK_VF1 << vf_number)) {
		ret_val = 0;
		hw->mbx.stats.acks++;
	}

	return ret_val;
}