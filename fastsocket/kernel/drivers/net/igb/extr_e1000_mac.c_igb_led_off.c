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
struct TYPE_4__ {int /*<<< orphan*/  ledctl_mode1; } ;
struct TYPE_3__ {int media_type; } ;
struct e1000_hw {TYPE_2__ mac; TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_LEDCTL ; 
#define  e1000_media_type_copper 128 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 igb_led_off(struct e1000_hw *hw)
{
	switch (hw->phy.media_type) {
	case e1000_media_type_copper:
		wr32(E1000_LEDCTL, hw->mac.ledctl_mode1);
		break;
	default:
		break;
	}

	return 0;
}