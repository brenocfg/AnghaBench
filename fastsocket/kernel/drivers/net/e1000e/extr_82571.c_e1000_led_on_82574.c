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
typedef  int u32 ;
struct TYPE_2__ {int ledctl_mode2; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int E1000_LEDCTL_LED0_IVRT ; 
 int E1000_LEDCTL_MODE_LED_ON ; 
 int E1000_STATUS_LU ; 
 int /*<<< orphan*/  LEDCTL ; 
 int /*<<< orphan*/  STATUS ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_led_on_82574(struct e1000_hw *hw)
{
	u32 ctrl;
	u32 i;

	ctrl = hw->mac.ledctl_mode2;
	if (!(E1000_STATUS_LU & er32(STATUS))) {
		/* If no link, then turn LED on by setting the invert bit
		 * for each LED that's "on" (0x0E) in ledctl_mode2.
		 */
		for (i = 0; i < 4; i++)
			if (((hw->mac.ledctl_mode2 >> (i * 8)) & 0xFF) ==
			    E1000_LEDCTL_MODE_LED_ON)
				ctrl |= (E1000_LEDCTL_LED0_IVRT << (i * 8));
	}
	ew32(LEDCTL, ctrl);

	return 0;
}