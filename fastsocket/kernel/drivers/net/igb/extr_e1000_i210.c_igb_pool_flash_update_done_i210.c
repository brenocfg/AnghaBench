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
typedef  scalar_t__ u32 ;
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EECD ; 
 scalar_t__ E1000_EECD_FLUDONE_I210 ; 
 int /*<<< orphan*/  E1000_ERR_NVM ; 
 scalar_t__ E1000_FLUDONE_ATTEMPTS ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 scalar_t__ rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 igb_pool_flash_update_done_i210(struct e1000_hw *hw)
{
	s32 ret_val = -E1000_ERR_NVM;
	u32 i, reg;

	for (i = 0; i < E1000_FLUDONE_ATTEMPTS; i++) {
		reg = rd32(E1000_EECD);
		if (reg & E1000_EECD_FLUDONE_I210) {
			ret_val = E1000_SUCCESS;
			break;
		}
		udelay(5);
	}

	return ret_val;
}