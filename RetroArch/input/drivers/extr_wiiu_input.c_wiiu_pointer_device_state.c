#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* joypad; } ;
typedef  TYPE_2__ wiiu_input_t ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  input_bits_t ;
struct TYPE_4__ {int (* axis ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* get_buttons ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  RETRO_DEVICE_ID_POINTER_PRESSED 130 
#define  RETRO_DEVICE_ID_POINTER_X 129 
#define  RETRO_DEVICE_ID_POINTER_Y 128 
 int /*<<< orphan*/  VPAD_BUTTON_TOUCH_BIT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 
 int stub3 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int16_t wiiu_pointer_device_state(wiiu_input_t* wiiu, unsigned id)
{
	switch (id)
	{
		case RETRO_DEVICE_ID_POINTER_PRESSED:
		{
			input_bits_t state;
			wiiu->joypad->get_buttons(0, &state);
			return BIT256_GET(state, VPAD_BUTTON_TOUCH_BIT) ? 1 : 0;
		}
		case RETRO_DEVICE_ID_POINTER_X:
			return wiiu->joypad->axis(0, 0xFFFF0004UL);
		case RETRO_DEVICE_ID_POINTER_Y:
			return wiiu->joypad->axis(0, 0xFFFF0005UL);
	}

	return 0;
}