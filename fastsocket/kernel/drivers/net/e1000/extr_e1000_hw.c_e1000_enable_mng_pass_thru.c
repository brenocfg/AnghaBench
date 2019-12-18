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
typedef  int u32 ;
struct e1000_hw {scalar_t__ asf_firmware_present; } ;

/* Variables and functions */
 int E1000_MANC_ASF_EN ; 
 int E1000_MANC_EN_MAC_ADDR_FILTER ; 
 int E1000_MANC_RCV_TCO_EN ; 
 int E1000_MANC_SMBUS_EN ; 
 int /*<<< orphan*/  MANC ; 
 int er32 (int /*<<< orphan*/ ) ; 

u32 e1000_enable_mng_pass_thru(struct e1000_hw *hw)
{
	u32 manc;

	if (hw->asf_firmware_present) {
		manc = er32(MANC);

		if (!(manc & E1000_MANC_RCV_TCO_EN) ||
		    !(manc & E1000_MANC_EN_MAC_ADDR_FILTER))
			return false;
		if ((manc & E1000_MANC_SMBUS_EN) && !(manc & E1000_MANC_ASF_EN))
			return true;
	}
	return false;
}