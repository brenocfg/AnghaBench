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
typedef  int /*<<< orphan*/  Window ;

/* Variables and functions */
 unsigned int Button1Mask ; 
 unsigned int Button2Mask ; 
 unsigned int Button3Mask ; 
 scalar_t__ INPUT_MOUSE_OFF ; 
 scalar_t__ INPUT_direct_mouse ; 
 int INPUT_mouse_buttons ; 
 int INPUT_mouse_delta_x ; 
 int INPUT_mouse_delta_y ; 
 scalar_t__ INPUT_mouse_mode ; 
 int INPUT_mouse_port ; 
 int* POKEY_POT_input ; 
 scalar_t__ XQueryPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*,int*,unsigned int*) ; 
 int /*<<< orphan*/  display ; 
 int /*<<< orphan*/  window ; 
 scalar_t__ window_height ; 
 scalar_t__ window_width ; 

void Atari_Mouse(void)
{
	static int last_x = 0;
	static int last_y = 0;
	Window root_return;
	Window child_return;
	int root_x_return;
	int root_y_return;
	int win_x_return;
	int win_y_return;
	unsigned int mask_return;

	if (INPUT_mouse_mode == INPUT_MOUSE_OFF)
		return;
	if (XQueryPointer(display, window, &root_return,
					  &child_return, &root_x_return, &root_y_return,
					  &win_x_return, &win_y_return, &mask_return)) {
		if(INPUT_direct_mouse) {
			int potx = win_x_return, poty = win_y_return;
			if(potx < 0) potx = 0;
			if(poty < 0) poty = 0;
			potx = (double)potx * (228.0 / (double)window_width);
			poty = (double)poty * (228.0 / (double)window_height);
			if(potx > 227) potx = 227;
			if(poty > 227) poty = 227;
			POKEY_POT_input[INPUT_mouse_port << 1] = 227 - potx;
			POKEY_POT_input[(INPUT_mouse_port << 1) + 1] = 227 - poty;
		} else {
			INPUT_mouse_delta_x = win_x_return - last_x;
			INPUT_mouse_delta_y = win_y_return - last_y;
			last_x = win_x_return;
			last_y = win_y_return;
		}

		INPUT_mouse_buttons = (mask_return & Button1Mask ? 1 : 0)
		              | (mask_return & Button3Mask ? 2 : 0)
		              | (mask_return & Button2Mask ? 4 : 0);
	}
}