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
typedef  int /*<<< orphan*/  ubyte ;
struct wiimote_t {short btns_last; short btns; short btns_held; short btns_released; } ;

/* Variables and functions */
 short BIG_ENDIAN_SHORT (short) ; 
 short WIIMOTE_BUTTON_ALL ; 

void wiiuse_pressed_buttons(struct wiimote_t* wm, ubyte* msg) {
	short now;

	/* convert to big endian */
	now = BIG_ENDIAN_SHORT(*(short*)msg) & WIIMOTE_BUTTON_ALL;

	/* preserve old btns pressed */
	wm->btns_last = wm->btns;

	/* pressed now & were pressed, then held */
	wm->btns_held = (now & wm->btns);

	/* were pressed or were held & not pressed now, then released */
	wm->btns_released = ((wm->btns | wm->btns_held) & ~now);

	/* buttons pressed now */
	wm->btns = now;
}