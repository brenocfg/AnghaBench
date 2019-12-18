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
 int Atari800_MACHINE_XLXE ; 
 void* Atari800_builtin_basic ; 
 void* Atari800_builtin_game ; 
 void* Atari800_f_keys ; 
 void* Atari800_jumper ; 
 void* Atari800_keyboard_detached ; 
 void* Atari800_keyboard_leds ; 
 int Atari800_machine_type ; 
 void* FALSE ; 

void Atari800_SetMachineType(int type)
{
	Atari800_machine_type = type;
	if (Atari800_machine_type != Atari800_MACHINE_XLXE) {
		Atari800_builtin_basic = FALSE;
		Atari800_keyboard_leds = FALSE;
		Atari800_f_keys = FALSE;
		Atari800_jumper = FALSE;
		Atari800_builtin_game = FALSE;
		Atari800_keyboard_detached = FALSE;
	}
}