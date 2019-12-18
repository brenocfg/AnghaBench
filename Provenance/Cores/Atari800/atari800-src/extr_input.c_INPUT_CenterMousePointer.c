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
#define  INPUT_MOUSE_AMIGA 136 
#define  INPUT_MOUSE_GUN 135 
#define  INPUT_MOUSE_JOY 134 
#define  INPUT_MOUSE_KOALA 133 
#define  INPUT_MOUSE_PAD 132 
#define  INPUT_MOUSE_PEN 131 
#define  INPUT_MOUSE_ST 130 
#define  INPUT_MOUSE_TOUCH 129 
#define  INPUT_MOUSE_TRAK 128 
 int INPUT_mouse_mode ; 
 int MOUSE_SHIFT ; 
 int /*<<< orphan*/  mouse_move_x ; 
 int /*<<< orphan*/  mouse_move_y ; 
 int mouse_x ; 
 int mouse_y ; 

void INPUT_CenterMousePointer(void)
{
	switch (INPUT_mouse_mode) {
	case INPUT_MOUSE_PAD:
	case INPUT_MOUSE_TOUCH:
	case INPUT_MOUSE_KOALA:
		mouse_x = 114 << MOUSE_SHIFT;
		mouse_y = 114 << MOUSE_SHIFT;
		break;
	case INPUT_MOUSE_PEN:
	case INPUT_MOUSE_GUN:
		mouse_x = 84 << MOUSE_SHIFT;
		mouse_y = 60 << MOUSE_SHIFT;
		break;
	case INPUT_MOUSE_AMIGA:
	case INPUT_MOUSE_ST:
	case INPUT_MOUSE_TRAK:
	case INPUT_MOUSE_JOY:
		mouse_move_x = 0;
		mouse_move_y = 0;
		break;
	}
}