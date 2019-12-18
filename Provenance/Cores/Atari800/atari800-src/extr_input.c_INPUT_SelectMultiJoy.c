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
 scalar_t__ Atari800_MACHINE_5200 ; 
 scalar_t__ Atari800_machine_type ; 
 int /*<<< orphan*/ * GTIA_TRIG ; 
 scalar_t__ INPUT_joy_multijoy ; 
 int* PIA_PORT_input ; 
 int* STICK ; 
 int /*<<< orphan*/ * TRIG_input ; 
 int joy_multijoy_no ; 

void INPUT_SelectMultiJoy(int no)
{
	no &= 3;
	joy_multijoy_no = no;
	if (INPUT_joy_multijoy && Atari800_machine_type != Atari800_MACHINE_5200) {
		PIA_PORT_input[0] = 0xf0 | STICK[no];
		GTIA_TRIG[0] = TRIG_input[no];
	}
}