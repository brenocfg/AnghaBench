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
 scalar_t__ Atari800_MACHINE_XLXE ; 
 scalar_t__ Atari800_jumper ; 
 scalar_t__ Atari800_machine_type ; 
 int* POKEY_POT_input ; 

void Atari800_UpdateJumper(void)
{
	if (Atari800_machine_type == Atari800_MACHINE_XLXE)
			POKEY_POT_input[4] = Atari800_jumper ? 0 : 228;
}