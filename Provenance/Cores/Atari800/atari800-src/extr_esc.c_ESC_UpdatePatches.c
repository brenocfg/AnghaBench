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
 scalar_t__ Atari800_MACHINE_800 ; 
 scalar_t__ Atari800_MACHINE_XLXE ; 
 scalar_t__ Atari800_machine_type ; 
 int /*<<< orphan*/  Devices_UpdatePatches () ; 
 int /*<<< orphan*/  ESC_PatchOS () ; 
 int /*<<< orphan*/  MEMORY_dCopyToMem (scalar_t__,int const,int) ; 
 scalar_t__ MEMORY_os ; 
 int PIA_PORTB ; 

void ESC_UpdatePatches(void)
{
	/* Patch only if OS enabled. */
	if (Atari800_machine_type != Atari800_MACHINE_5200 &&
	    (Atari800_machine_type != Atari800_MACHINE_XLXE || (PIA_PORTB & 1) != 0)) {
		int const os_rom_start = Atari800_machine_type == Atari800_MACHINE_800 ? 0xd800 : 0xc000;
		/* Restore unpatched OS */
		if (os_rom_start < 0xd000)
			MEMORY_dCopyToMem(MEMORY_os, os_rom_start, 0xd000 - os_rom_start);
		MEMORY_dCopyToMem(MEMORY_os + 0xd800 - os_rom_start, 0xd800, 0x2800);
		/* Set patches */
		ESC_PatchOS();
		Devices_UpdatePatches();
	}
}