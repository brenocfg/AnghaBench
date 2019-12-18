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
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_SCTL_DISABLE_SERDES_LOOPBACK ; 
 int /*<<< orphan*/  SCTL ; 
#define  e1000_82571 129 
#define  e1000_82572 128 
 int /*<<< orphan*/  e1000e_setup_fiber_serdes_link (struct e1000_hw*) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_setup_fiber_serdes_link_82571(struct e1000_hw *hw)
{
	switch (hw->mac.type) {
	case e1000_82571:
	case e1000_82572:
		/* If SerDes loopback mode is entered, there is no form
		 * of reset to take the adapter out of that mode.  So we
		 * have to explicitly take the adapter out of loopback
		 * mode.  This prevents drivers from twiddling their thumbs
		 * if another tool failed to take it out of loopback mode.
		 */
		ew32(SCTL, E1000_SCTL_DISABLE_SERDES_LOOPBACK);
		break;
	default:
		break;
	}

	return e1000e_setup_fiber_serdes_link(hw);
}