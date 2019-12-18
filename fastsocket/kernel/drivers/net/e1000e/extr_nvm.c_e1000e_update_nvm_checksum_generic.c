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
typedef  scalar_t__ u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ NVM_CHECKSUM_REG ; 
 scalar_t__ NVM_SUM ; 
 scalar_t__ e1000_read_nvm (struct e1000_hw*,scalar_t__,int,scalar_t__*) ; 
 scalar_t__ e1000_write_nvm (struct e1000_hw*,scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

s32 e1000e_update_nvm_checksum_generic(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 checksum = 0;
	u16 i, nvm_data;

	for (i = 0; i < NVM_CHECKSUM_REG; i++) {
		ret_val = e1000_read_nvm(hw, i, 1, &nvm_data);
		if (ret_val) {
			e_dbg("NVM Read Error while updating checksum.\n");
			return ret_val;
		}
		checksum += nvm_data;
	}
	checksum = (u16)NVM_SUM - checksum;
	ret_val = e1000_write_nvm(hw, NVM_CHECKSUM_REG, 1, &checksum);
	if (ret_val)
		e_dbg("NVM Write Error while updating checksum.\n");

	return ret_val;
}