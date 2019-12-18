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
 scalar_t__ INPUT_MOUSE_AMIGA ; 
 scalar_t__ INPUT_MOUSE_TRAK ; 
 scalar_t__ INPUT_mouse_mode ; 
 size_t INPUT_mouse_port ; 
 int* PIA_PORT_input ; 
 int* STICK ; 
 scalar_t__ max_scanline_counter ; 
 int* mouse_amiga_codes ; 
 int mouse_last_down ; 
 int mouse_last_right ; 
 int* mouse_st_codes ; 
 int /*<<< orphan*/  mouse_step () ; 
 int mouse_x ; 
 int mouse_y ; 
 scalar_t__ scanline_counter ; 

void INPUT_Scanline(void)
{
	if (--scanline_counter == 0) {
		mouse_step();
		if (INPUT_mouse_mode == INPUT_MOUSE_TRAK) {
			/* bit 3 toggles - vertical movement, bit 2 = 0 - up */
			/* bit 1 toggles - horizontal movement, bit 0 = 0 - left */
			STICK[INPUT_mouse_port] = ((mouse_y & 1) << 3) | (mouse_last_down << 2)
								| ((mouse_x & 1) << 1) | mouse_last_right;
		}
		else {
			STICK[INPUT_mouse_port] = (INPUT_mouse_mode == INPUT_MOUSE_AMIGA ? mouse_amiga_codes : mouse_st_codes)
								[(mouse_y & 3) * 4 + (mouse_x & 3)];
		}
		PIA_PORT_input[0] = (STICK[1] << 4) | STICK[0];
		PIA_PORT_input[1] = (STICK[3] << 4) | STICK[2];
		scanline_counter = max_scanline_counter;
	}
}