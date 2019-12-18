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
struct classic_ctrl_t {short btns_last; short btns; short btns_held; short btns_released; } ;

/* Variables and functions */
 short CLASSIC_CTRL_BUTTON_ALL ; 

__attribute__((used)) static void classic_ctrl_pressed_buttons(struct classic_ctrl_t* cc, short now) {
	/* message is inverted (0 is active, 1 is inactive) */
	now = ~now & CLASSIC_CTRL_BUTTON_ALL;

	/* preserve old btns pressed */
	cc->btns_last = cc->btns;

	/* pressed now & were pressed, then held */
	cc->btns_held = (now & cc->btns);

	/* were pressed or were held & not pressed now, then released */
	cc->btns_released = ((cc->btns | cc->btns_held) & ~now);

	/* buttons pressed now */
	cc->btns = now;
}