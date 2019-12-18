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
 int /*<<< orphan*/  Atari800_UpdateJumper () ; 
 int /*<<< orphan*/  Atari800_UpdateKeyboardDetached () ; 
 int /*<<< orphan*/  Devices_UpdatePatches () ; 
 int /*<<< orphan*/  ESC_ClearAll () ; 
 int FALSE ; 
 int /*<<< orphan*/  MEMORY_InitialiseMachine () ; 
 int TRUE ; 
 int /*<<< orphan*/  load_roms () ; 

int Atari800_InitialiseMachine(void)
{
	ESC_ClearAll();
	if (!load_roms())
		return FALSE;
	Atari800_UpdateKeyboardDetached();
	Atari800_UpdateJumper();
	MEMORY_InitialiseMachine();
	Devices_UpdatePatches();
	return TRUE;
}