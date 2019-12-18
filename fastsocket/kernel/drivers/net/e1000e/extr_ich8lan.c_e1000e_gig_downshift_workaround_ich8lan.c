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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_2__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_DIAG_NELPBK ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_DIAG_OFFSET ; 
 scalar_t__ e1000_ich8lan ; 
 scalar_t__ e1000_phy_ife ; 
 scalar_t__ e1000e_read_kmrn_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000e_write_kmrn_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void e1000e_gig_downshift_workaround_ich8lan(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 reg_data;

	if ((hw->mac.type != e1000_ich8lan) || (hw->phy.type == e1000_phy_ife))
		return;

	ret_val = e1000e_read_kmrn_reg(hw, E1000_KMRNCTRLSTA_DIAG_OFFSET,
				      &reg_data);
	if (ret_val)
		return;
	reg_data |= E1000_KMRNCTRLSTA_DIAG_NELPBK;
	ret_val = e1000e_write_kmrn_reg(hw, E1000_KMRNCTRLSTA_DIAG_OFFSET,
				       reg_data);
	if (ret_val)
		return;
	reg_data &= ~E1000_KMRNCTRLSTA_DIAG_NELPBK;
	e1000e_write_kmrn_reg(hw, E1000_KMRNCTRLSTA_DIAG_OFFSET, reg_data);
}