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
 scalar_t__ Large ; 
 scalar_t__ Small ; 
 int /*<<< orphan*/  XQueryPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*,int*,unsigned int*) ; 
 int /*<<< orphan*/  display ; 
 int mouse_stick ; 
 int /*<<< orphan*/  window ; 
 int window_height ; 
 int window_width ; 
 scalar_t__ windowsize ; 

__attribute__((used)) static void mouse_joystick(int mode)
{
	Window root_return;
	Window child_return;
	int root_x_return;
	int root_y_return;
	int win_x_return;
	int win_y_return;
	unsigned int mask_return;

	mouse_stick = 0x0f;

	XQueryPointer(display, window, &root_return, &child_return,
				  &root_x_return, &root_y_return,
				  &win_x_return, &win_y_return,
				  &mask_return);

	if (mode < 5) {
		int center_x;
		int center_y;
		int threshold;

		if (windowsize == Small) {
			center_x = window_width / 2;
			center_y = window_height / 2;
			threshold = 32;
		}
		else if (windowsize == Large) {
			center_x = window_width / 2;
			center_y = window_height / 2;
			threshold = 64;
		}
		else {
			center_x = window_width / 2;
			center_y = window_height / 2;
			threshold = 96;
		}

		if (win_x_return < 0 || win_x_return > center_x * 2 ||
		    win_y_return < 0 || win_y_return > center_y * 2 )
			mouse_stick = 0x0f;
		else
		{
		if (win_x_return < (center_x - threshold))
			mouse_stick &= 0xfb;
		if (win_x_return > (center_x + threshold))
			mouse_stick &= 0xf7;
		if (win_y_return < (center_y - threshold))
			mouse_stick &= 0xfe;
		if (win_y_return > (center_y + threshold))
			mouse_stick &= 0xfd;
		}
	}
	else {
		if (mask_return)
			mouse_stick &= 0xfb;
	}
}