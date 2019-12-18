#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ e1000_82571 ; 
 scalar_t__ e1000_check_alt_mac_addr_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_read_mac_addr_generic (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_read_mac_addr_82571(struct e1000_hw *hw)
{
	if (hw->mac.type == e1000_82571) {
		s32 ret_val;

		/* If there's an alternate MAC address place it in RAR0
		 * so that it will override the Si installed default perm
		 * address.
		 */
		ret_val = e1000_check_alt_mac_addr_generic(hw);
		if (ret_val)
			return ret_val;
	}

	return e1000_read_mac_addr_generic(hw);
}