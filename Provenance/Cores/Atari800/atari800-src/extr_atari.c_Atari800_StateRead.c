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
typedef  int UBYTE ;

/* Variables and functions */
 int Atari800_MACHINE_5200 ; 
 int Atari800_MACHINE_800 ; 
 int Atari800_MACHINE_SIZE ; 
 int Atari800_MACHINE_XLXE ; 
 int /*<<< orphan*/  Atari800_SetMachineType (int) ; 
 int /*<<< orphan*/  Atari800_SetTVMode (int) ; 
 int Atari800_TV_NTSC ; 
 int Atari800_TV_PAL ; 
 int /*<<< orphan*/  Atari800_UpdateJumper () ; 
 int /*<<< orphan*/  Atari800_UpdateKeyboardDetached () ; 
 int Atari800_builtin_basic ; 
 int Atari800_builtin_game ; 
 int Atari800_f_keys ; 
 int Atari800_jumper ; 
 int Atari800_keyboard_detached ; 
 int Atari800_keyboard_leds ; 
 int Atari800_machine_type ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int MEMORY_RAM_320_COMPY_SHOP ; 
 int MEMORY_ram_size ; 
 int /*<<< orphan*/  StateSav_ReadINT (int*,int) ; 
 int /*<<< orphan*/  StateSav_ReadUBYTE (int*,int) ; 
 int /*<<< orphan*/  load_roms () ; 

void Atari800_StateRead(UBYTE version)
{
	if (version >= 7) {
		UBYTE temp;
		StateSav_ReadUBYTE(&temp, 1);
		Atari800_SetTVMode(temp ? Atari800_TV_PAL : Atari800_TV_NTSC);
		StateSav_ReadUBYTE(&temp, 1);
		if (temp < 0 || temp >= Atari800_MACHINE_SIZE) {
			temp = Atari800_MACHINE_XLXE;
			Log_print("Warning: Bad machine type read in from state save, defaulting to XL/XE");
		}
		Atari800_SetMachineType(temp);
		if (Atari800_machine_type == Atari800_MACHINE_XLXE) {
			StateSav_ReadUBYTE(&temp, 1);
			Atari800_builtin_basic = temp != 0;
			StateSav_ReadUBYTE(&temp, 1);
			Atari800_keyboard_leds = temp != 0;
			StateSav_ReadUBYTE(&temp, 1);
			Atari800_f_keys = temp != 0;
			StateSav_ReadUBYTE(&temp, 1);
			Atari800_jumper = temp != 0;
			Atari800_UpdateJumper();
			StateSav_ReadUBYTE(&temp, 1);
			Atari800_builtin_game = temp != 0;
			StateSav_ReadUBYTE(&temp, 1);
			Atari800_keyboard_detached = temp != 0;
			Atari800_UpdateKeyboardDetached();
		}
	}
	else { /* savestate from version 2.2.1 or earlier */
		int new_tv_mode;
		/* these are all for compatibility with previous versions */
		UBYTE temp;
		int default_tv_mode;
		int os;
		int default_system;
		int pil_on;

		StateSav_ReadUBYTE(&temp, 1);
		new_tv_mode = (temp == 0) ? Atari800_TV_PAL : Atari800_TV_NTSC;
		Atari800_SetTVMode(new_tv_mode);

		StateSav_ReadUBYTE(&temp, 1);
		StateSav_ReadINT(&os, 1);
		switch (temp) {
		case 0:
			Atari800_machine_type = Atari800_MACHINE_800;
			MEMORY_ram_size = 48;
			break;
		case 1:
			Atari800_machine_type = Atari800_MACHINE_XLXE;
			MEMORY_ram_size = 64;
			break;
		case 2:
			Atari800_machine_type = Atari800_MACHINE_XLXE;
			MEMORY_ram_size = 128;
			break;
		case 3:
			Atari800_machine_type = Atari800_MACHINE_XLXE;
			MEMORY_ram_size = MEMORY_RAM_320_COMPY_SHOP;
			break;
		case 4:
			Atari800_machine_type = Atari800_MACHINE_5200;
			MEMORY_ram_size = 16;
			break;
		case 5:
			Atari800_machine_type = Atari800_MACHINE_800;
			MEMORY_ram_size = 16;
			break;
		case 6:
			Atari800_machine_type = Atari800_MACHINE_XLXE;
			MEMORY_ram_size = 16;
			break;
		case 7:
			Atari800_machine_type = Atari800_MACHINE_XLXE;
			MEMORY_ram_size = 576;
			break;
		case 8:
			Atari800_machine_type = Atari800_MACHINE_XLXE;
			MEMORY_ram_size = 1088;
			break;
		case 9:
			Atari800_machine_type = Atari800_MACHINE_XLXE;
			MEMORY_ram_size = 192;
			break;
		default:
			Atari800_machine_type = Atari800_MACHINE_XLXE;
			MEMORY_ram_size = 64;
			Log_print("Warning: Bad machine type read in from state save, defaulting to 800 XL");
			break;
		}

		StateSav_ReadINT(&pil_on, 1);
		StateSav_ReadINT(&default_tv_mode, 1);
		StateSav_ReadINT(&default_system, 1);
		Atari800_SetMachineType(Atari800_machine_type);
	}
	load_roms();
	/* XXX: what about patches? */
}