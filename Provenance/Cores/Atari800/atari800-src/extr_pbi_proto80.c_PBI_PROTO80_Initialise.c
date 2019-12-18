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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  Atari800_LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int PBI_D6D7ram ; 
 int PBI_PROTO80_enabled ; 
 int TRUE ; 
 scalar_t__ Util_malloc (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proto80_rom_filename ; 
 int /*<<< orphan*/ * proto80rom ; 
 scalar_t__ strcmp (char*,char*) ; 

int PBI_PROTO80_Initialise(int *argc, char *argv[])
{
	int i, j;
	for (i = j = 1; i < *argc; i++) {
		if (strcmp(argv[i], "-proto80") == 0) {
			Log_print("proto80 enabled");
			PBI_PROTO80_enabled = TRUE;
		}
		else {
		 	if (strcmp(argv[i], "-help") == 0) {
				Log_print("\t-proto80         Emulate a prototype 80 column board for the 1090");
			}
			argv[j++] = argv[i];
		}
	}
	*argc = j;

	if (PBI_PROTO80_enabled) {
		proto80rom = (UBYTE *)Util_malloc(0x800);
		if (!Atari800_LoadImage(proto80_rom_filename, proto80rom, 0x800)) {
			free(proto80rom);
			PBI_PROTO80_enabled = FALSE;
			Log_print("Couldn't load proto80 rom image");
			return FALSE;
		}
		else {
			Log_print("loaded proto80 rom image");
			PBI_D6D7ram = TRUE;
		}
	}

	return TRUE;
}