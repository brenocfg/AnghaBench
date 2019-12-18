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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  HV_KMRN_MDIO_SLOW ; 
 int /*<<< orphan*/  HV_KMRN_MODE_CTRL ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_set_mdio_slow_mode_hv(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 data;

	ret_val = e1e_rphy(hw, HV_KMRN_MODE_CTRL, &data);
	if (ret_val)
		return ret_val;

	data |= HV_KMRN_MDIO_SLOW;

	ret_val = e1e_wphy(hw, HV_KMRN_MODE_CTRL, data);

	return ret_val;
}