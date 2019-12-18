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
 scalar_t__ ID_LED_DEFAULT ; 
 scalar_t__ ID_LED_RESERVED_0000 ; 
 scalar_t__ ID_LED_RESERVED_FFFF ; 
 int /*<<< orphan*/  NVM_ID_LED_SETTINGS ; 
 scalar_t__ e1000_read_nvm (struct e1000_hw*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

s32 e1000e_valid_led_default(struct e1000_hw *hw, u16 *data)
{
	s32 ret_val;

	ret_val = e1000_read_nvm(hw, NVM_ID_LED_SETTINGS, 1, data);
	if (ret_val) {
		e_dbg("NVM Read Error\n");
		return ret_val;
	}

	if (*data == ID_LED_RESERVED_0000 || *data == ID_LED_RESERVED_FFFF)
		*data = ID_LED_DEFAULT;

	return 0;
}