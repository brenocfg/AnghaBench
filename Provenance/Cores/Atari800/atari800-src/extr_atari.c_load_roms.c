#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 scalar_t__ Atari800_LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Atari800_MACHINE_5200 ; 
 scalar_t__ Atari800_MACHINE_800 ; 
 int Atari800_builtin_basic ; 
 int Atari800_builtin_game ; 
 scalar_t__ Atari800_machine_type ; 
 int Atari800_os_version ; 
 int /*<<< orphan*/  Atari800_tv_mode ; 
 int /*<<< orphan*/  COPY_EMUOS (int) ; 
 int FALSE ; 
 int /*<<< orphan*/  MEMORY_basic ; 
 int MEMORY_have_basic ; 
 int /*<<< orphan*/  MEMORY_os ; 
 int /*<<< orphan*/  MEMORY_ram_size ; 
 scalar_t__ MEMORY_xe_bank ; 
 int /*<<< orphan*/  MEMORY_xegame ; 
 int /*<<< orphan*/  SYSROM_ChooseROMs (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 TYPE_1__* SYSROM_roms ; 
 int TRUE ; 
 int emuos_mode ; 

__attribute__((used)) static int load_roms(void)
{
	if (Atari800_machine_type != Atari800_MACHINE_5200 && emuos_mode == 2) {
		COPY_EMUOS(Atari800_machine_type == Atari800_MACHINE_800 ? 0x800 : 0x2000);
		Atari800_os_version = -1;
	}
	else {
		int basic_ver, xegame_ver;
		SYSROM_ChooseROMs(Atari800_machine_type, MEMORY_ram_size, Atari800_tv_mode, &Atari800_os_version, &basic_ver, &xegame_ver);
		if (Atari800_os_version == -1
		    || !Atari800_LoadImage(SYSROM_roms[Atari800_os_version].filename, MEMORY_os, SYSROM_roms[Atari800_os_version].size)) {
			/* Missing OS ROM. */
			Atari800_os_version = -1;
			if (Atari800_machine_type != Atari800_MACHINE_5200 && emuos_mode == 1)
				COPY_EMUOS(Atari800_machine_type == Atari800_MACHINE_800 ? 0x800 : 0x2000);
			else
				/* No OS ROM loaded. */
				return FALSE;
		}
		else if (Atari800_machine_type != Atari800_MACHINE_5200) {
			/* OS ROM found, try loading BASIC. */
			MEMORY_have_basic = basic_ver != -1 && Atari800_LoadImage(SYSROM_roms[basic_ver].filename, MEMORY_basic, SYSROM_roms[basic_ver].size);
			if (!MEMORY_have_basic)
				/* Missing BASIC ROM. Don't fail when it happens. */
				Atari800_builtin_basic = FALSE;

			if (Atari800_builtin_game) {
				/* Try loading built-in XEGS game. */
				if (xegame_ver == -1
				    || !Atari800_LoadImage(SYSROM_roms[xegame_ver].filename, MEMORY_xegame, SYSROM_roms[xegame_ver].size))
					/* Missing XEGS game ROM. */
					Atari800_builtin_game = FALSE;
			}
		}
	}

	MEMORY_xe_bank = 0;
	return TRUE;
}