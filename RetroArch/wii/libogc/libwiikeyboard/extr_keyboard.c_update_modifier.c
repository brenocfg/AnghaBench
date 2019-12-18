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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ KEYBOARD_PRESSED ; 
 scalar_t__ KEYBOARD_RELEASED ; 
 int _modifiers ; 

void update_modifier(u_int type, int toggle, int mask) {
	if (toggle) {
		if (type == KEYBOARD_PRESSED)
			_modifiers ^= mask;
	} else {
		if (type == KEYBOARD_RELEASED)
			_modifiers &= ~mask;
		else
			_modifiers |= mask;
	}
}