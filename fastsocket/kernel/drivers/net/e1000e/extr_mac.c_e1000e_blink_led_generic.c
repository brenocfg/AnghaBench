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
typedef  int u32 ;
struct TYPE_4__ {int ledctl_mode2; int ledctl_default; } ;
struct TYPE_3__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_2__ mac; TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int E1000_LEDCTL_LED0_BLINK ; 
 int E1000_LEDCTL_LED0_IVRT ; 
 int E1000_LEDCTL_LED0_MODE_MASK ; 
 int E1000_LEDCTL_LED0_MODE_SHIFT ; 
 int E1000_LEDCTL_MODE_LED_OFF ; 
 int E1000_LEDCTL_MODE_LED_ON ; 
 int /*<<< orphan*/  LEDCTL ; 
 scalar_t__ e1000_media_type_fiber ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

s32 e1000e_blink_led_generic(struct e1000_hw *hw)
{
	u32 ledctl_blink = 0;
	u32 i;

	if (hw->phy.media_type == e1000_media_type_fiber) {
		/* always blink LED0 for PCI-E fiber */
		ledctl_blink = E1000_LEDCTL_LED0_BLINK |
		    (E1000_LEDCTL_MODE_LED_ON << E1000_LEDCTL_LED0_MODE_SHIFT);
	} else {
		/* Set the blink bit for each LED that's "on" (0x0E)
		 * (or "off" if inverted) in ledctl_mode2.  The blink
		 * logic in hardware only works when mode is set to "on"
		 * so it must be changed accordingly when the mode is
		 * "off" and inverted.
		 */
		ledctl_blink = hw->mac.ledctl_mode2;
		for (i = 0; i < 32; i += 8) {
			u32 mode = (hw->mac.ledctl_mode2 >> i) &
			    E1000_LEDCTL_LED0_MODE_MASK;
			u32 led_default = hw->mac.ledctl_default >> i;

			if ((!(led_default & E1000_LEDCTL_LED0_IVRT) &&
			     (mode == E1000_LEDCTL_MODE_LED_ON)) ||
			    ((led_default & E1000_LEDCTL_LED0_IVRT) &&
			     (mode == E1000_LEDCTL_MODE_LED_OFF))) {
				ledctl_blink &=
				    ~(E1000_LEDCTL_LED0_MODE_MASK << i);
				ledctl_blink |= (E1000_LEDCTL_LED0_BLINK |
						 E1000_LEDCTL_MODE_LED_ON) << i;
			}
		}
	}

	ew32(LEDCTL, ledctl_blink);

	return 0;
}