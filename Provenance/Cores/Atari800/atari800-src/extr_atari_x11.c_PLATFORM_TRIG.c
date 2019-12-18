#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Window ;
struct TYPE_3__ {int buttons; } ;

/* Variables and functions */
 unsigned int Button1Mask ; 
 int JS_RETURN ; 
 scalar_t__ XQueryPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*,int*,unsigned int*) ; 
 int /*<<< orphan*/  display ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  js0 ; 
 int js0_mode ; 
 int /*<<< orphan*/  js1 ; 
 int js1_mode ; 
 TYPE_1__ js_data ; 
 int keypad_mode ; 
 int keypad_trig ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  window ; 
 int window_height ; 
 int window_width ; 
 int xmouse_mode ; 

int PLATFORM_TRIG(int num)
{
	int trig = 1;				/* Trigger not pressed */

	if (num == keypad_mode) {
		trig = keypad_trig;
	}
	if (num == xmouse_mode) {
		Window root_return;
		Window child_return;
		int root_x_return;
		int root_y_return;
		int win_x_return;
		int win_y_return;
		unsigned int mask_return;

		if (XQueryPointer(display, window, &root_return, &child_return,
						  &root_x_return, &root_y_return,
						  &win_x_return, &win_y_return,
						  &mask_return)) {
			if (win_x_return < 0 || win_x_return > window_width ||
			    win_y_return < 0 || win_y_return > window_height)
				trig = 1;
			else if (mask_return & Button1Mask)
				trig = 0;
		}
	}
#ifdef LINUX_JOYSTICK
	if (num == js0_mode) {
		int status;

		status = read(js0, &js_data, JS_RETURN);
		if (status != JS_RETURN) {
			perror("/dev/js0");
			exit(1);
		}
		if (js_data.buttons & 0x01)
			trig = 0;
		else
			trig = 1;
	}
	if (num == js1_mode) {
		int status;

		status = read(js1, &js_data, JS_RETURN);
		if (status != JS_RETURN) {
			perror("/dev/js1");
			exit(1);
		}
		trig = (js_data.buttons & 0x0f) ? 0 : 1;
	}
#endif

	return trig;
}