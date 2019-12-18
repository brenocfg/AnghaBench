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
 int /*<<< orphan*/  Atari800_Coldstart () ; 
 scalar_t__ Atari800_MACHINE_5200 ; 
 scalar_t__ Atari800_machine_type ; 
 scalar_t__ BINLOAD_LOADING_BASIC_LISTED ; 
 scalar_t__ BINLOAD_LOADING_BASIC_SAVED ; 
 int /*<<< orphan*/ * BINLOAD_bin_file ; 
 scalar_t__ BINLOAD_loading_basic ; 
 int BINLOAD_start_binloading ; 
 int /*<<< orphan*/  ESC_UpdatePatches () ; 
 int FALSE ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int /*<<< orphan*/  SIO_DisableDrive (int) ; 
 scalar_t__ SIO_NO_DISK ; 
 scalar_t__* SIO_drive_status ; 
 int TRUE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (int*,int,int,int /*<<< orphan*/ *) ; 

int BINLOAD_Loader(const char *filename)
{
	UBYTE buf[2];
	if (BINLOAD_bin_file != NULL) {		/* close previously open file */
		fclose(BINLOAD_bin_file);
		BINLOAD_bin_file = NULL;
		BINLOAD_loading_basic = 0;
	}
	if (Atari800_machine_type == Atari800_MACHINE_5200) {
		Log_print("binload: can't run Atari programs directly on the 5200");
		return FALSE;
	}
	BINLOAD_bin_file = fopen(filename, "rb");
	if (BINLOAD_bin_file == NULL) {	/* open */
		Log_print("binload: can't open \"%s\"", filename);
		return FALSE;
	}
	/* Avoid "BOOT ERROR" when loading a BASIC program */
	if (SIO_drive_status[0] == SIO_NO_DISK)
		SIO_DisableDrive(1);
	if (fread(buf, 1, 2, BINLOAD_bin_file) == 2) {
		if (buf[0] == 0xff && buf[1] == 0xff) {
			BINLOAD_start_binloading = TRUE; /* force SIO to call BINLOAD_LoaderStart at boot */
			Atari800_Coldstart();             /* reboot */
			return TRUE;
		}
		else if (buf[0] == 0 && buf[1] == 0) {
			BINLOAD_loading_basic = BINLOAD_LOADING_BASIC_SAVED;
			ESC_UpdatePatches();
			Atari800_Coldstart();
			return TRUE;
		}
		else if (buf[0] >= '0' && buf[0] <= '9') {
			BINLOAD_loading_basic = BINLOAD_LOADING_BASIC_LISTED;
			ESC_UpdatePatches();
			Atari800_Coldstart();
			return TRUE;
		}
	}
	fclose(BINLOAD_bin_file);
	BINLOAD_bin_file = NULL;
	Log_print("binload: \"%s\" not recognized as a DOS or BASIC program", filename);
	return FALSE;
}