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

int suncore_mouse_baud_detection(unsigned char ch, int is_break)
{
	static int mouse_got_break = 0;
	static int ctr = 0;

	if (is_break) {
		/* Let a few normal bytes go by before we jump the gun
		 * and say we need to try another baud rate.
		 */
		if (mouse_got_break && ctr < 8)
			return 1;

		/* Ok, we need to try another baud. */
		ctr = 0;
		mouse_got_break = 1;
		return 2;
	}
	if (mouse_got_break) {
		ctr++;
		if (ch == 0x87) {
			/* Correct baud rate determined. */
			mouse_got_break = 0;
		}
		return 1;
	}
	return 0;
}