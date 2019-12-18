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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ (* check_for_link ) (struct e1000_hw*) ;} ;
struct e1000_mac_info {int autoneg_failed; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_mac_info mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_STATUS_LU ; 
 scalar_t__ FIBER_LINK_UP_LIMIT ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 scalar_t__ er32 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 e1000_poll_fiber_serdes_link_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 i, status;
	s32 ret_val;

	/* If we have a signal (the cable is plugged in, or assumed true for
	 * serdes media) then poll for a "Link-Up" indication in the Device
	 * Status Register.  Time-out if a link isn't seen in 500 milliseconds
	 * seconds (Auto-negotiation should complete in less than 500
	 * milliseconds even if the other end is doing it in SW).
	 */
	for (i = 0; i < FIBER_LINK_UP_LIMIT; i++) {
		usleep_range(10000, 20000);
		status = er32(STATUS);
		if (status & E1000_STATUS_LU)
			break;
	}
	if (i == FIBER_LINK_UP_LIMIT) {
		e_dbg("Never got a valid link from auto-neg!!!\n");
		mac->autoneg_failed = true;
		/* AutoNeg failed to achieve a link, so we'll call
		 * mac->check_for_link. This routine will force the
		 * link up if we detect a signal. This will allow us to
		 * communicate with non-autonegotiating link partners.
		 */
		ret_val = mac->ops.check_for_link(hw);
		if (ret_val) {
			e_dbg("Error while checking for link\n");
			return ret_val;
		}
		mac->autoneg_failed = false;
	} else {
		mac->autoneg_failed = false;
		e_dbg("Valid Link Found\n");
	}

	return 0;
}