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
struct TYPE_4__ {int /*<<< orphan*/  ledctl_default; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_2__ mac; TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IFE_PHY_SPECIAL_CONTROL_LED ; 
 int /*<<< orphan*/  LEDCTL ; 
 scalar_t__ e1000_phy_ife ; 
 int /*<<< orphan*/  e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_cleanup_led_ich8lan(struct e1000_hw *hw)
{
	if (hw->phy.type == e1000_phy_ife)
		return e1e_wphy(hw, IFE_PHY_SPECIAL_CONTROL_LED, 0);

	ew32(LEDCTL, hw->mac.ledctl_default);
	return 0;
}