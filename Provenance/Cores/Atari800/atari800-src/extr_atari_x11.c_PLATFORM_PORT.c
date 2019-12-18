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

/* Variables and functions */
 scalar_t__ INPUT_MOUSE_OFF ; 
 scalar_t__ INPUT_mouse_mode ; 
 int /*<<< orphan*/  js0 ; 
 int /*<<< orphan*/  js0_centre_x ; 
 int /*<<< orphan*/  js0_centre_y ; 
 int js0_mode ; 
 int /*<<< orphan*/  js1 ; 
 int /*<<< orphan*/  js1_centre_x ; 
 int /*<<< orphan*/  js1_centre_y ; 
 int js1_mode ; 
 int keypad_mode ; 
 int keypad_stick ; 
 int /*<<< orphan*/  mouse_joystick (int) ; 
 int mouse_stick ; 
 int /*<<< orphan*/  read_joystick (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xmouse_mode ; 

int PLATFORM_PORT(int num)
{
	int nibble_0 = 0x0f;
	int nibble_1 = 0x0f;

	if (num == 0) {
		if (keypad_mode == 0)
			nibble_0 = keypad_stick;
		else if (keypad_mode == 1)
			nibble_1 = keypad_stick;

		if (INPUT_mouse_mode == INPUT_MOUSE_OFF) {
			if (xmouse_mode == 0) {
				mouse_joystick(xmouse_mode);
				nibble_0 = mouse_stick;
			}
			else if (xmouse_mode == 1) {
				mouse_joystick(xmouse_mode);
				nibble_1 = mouse_stick;
			}
		}
#ifdef LINUX_JOYSTICK
		if (js0_mode == 0) {
			read_joystick(js0, js0_centre_x, js0_centre_y);
			nibble_0 = mouse_stick;
		}
		else if (js0_mode == 1) {
			read_joystick(js0, js0_centre_x, js0_centre_y);
			nibble_1 = mouse_stick;
		}
		if (js1_mode == 0) {
			read_joystick(js1, js1_centre_x, js1_centre_y);
			nibble_0 = mouse_stick;
		}
		else if (js1_mode == 1) {
			read_joystick(js1, js1_centre_x, js1_centre_y);
			nibble_1 = mouse_stick;
		}
#endif
	}
	else {
		if (keypad_mode == 2)
			nibble_0 = keypad_stick;
		else if (keypad_mode == 3)
			nibble_1 = keypad_stick;

		if (INPUT_mouse_mode == INPUT_MOUSE_OFF) {
			if (xmouse_mode == 2) {
				mouse_joystick(xmouse_mode);
				nibble_0 = mouse_stick;
			}
			else if (xmouse_mode == 3) {
				mouse_joystick(xmouse_mode);
				nibble_1 = mouse_stick;
			}
		}

#ifdef LINUX_JOYSTICK
		if (js0_mode == 2) {
			read_joystick(js0, js0_centre_x, js0_centre_y);
			nibble_0 = mouse_stick;
		}
		else if (js0_mode == 3) {
			read_joystick(js0, js0_centre_x, js0_centre_y);
			nibble_1 = mouse_stick;
		}
		if (js1_mode == 2) {
			read_joystick(js1, js1_centre_x, js1_centre_y);
			nibble_0 = mouse_stick;
		}
		else if (js1_mode == 3) {
			read_joystick(js1, js1_centre_x, js1_centre_y);
			nibble_1 = mouse_stick;
		}
#endif
	}

	return (nibble_1 << 4) | nibble_0;
}