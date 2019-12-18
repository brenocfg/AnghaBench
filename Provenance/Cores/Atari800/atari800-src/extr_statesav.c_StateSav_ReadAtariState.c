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
 int /*<<< orphan*/  ANTIC_StateRead () ; 
 int /*<<< orphan*/  Atari800_StateRead (int) ; 
 int /*<<< orphan*/  CARTRIDGE_StateRead (int) ; 
 int /*<<< orphan*/  CPU_StateRead (int,int) ; 
 int /*<<< orphan*/  DCStateRead () ; 
 int FALSE ; 
 int /*<<< orphan*/  GTIA_StateRead (int) ; 
 int /*<<< orphan*/  GZCLOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GZOPEN (char const*,char const*) ; 
 scalar_t__ GZREAD (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  GetGZErrorText () ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int /*<<< orphan*/  PBI_BB_StateRead () ; 
 int /*<<< orphan*/  PBI_MIO_StateRead () ; 
 int /*<<< orphan*/  PBI_StateRead () ; 
 int /*<<< orphan*/  PBI_XLD_StateRead () ; 
 int /*<<< orphan*/  PIA_StateRead (int) ; 
 int /*<<< orphan*/  POKEY_StateRead () ; 
 int SAVE_VERSION_NUMBER ; 
 int /*<<< orphan*/  SIO_StateRead () ; 
 int /*<<< orphan*/ * StateFile ; 
 int /*<<< orphan*/  StateSav_ReadINT (int*,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  XEP80_StateRead () ; 
 scalar_t__ Z_OK ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ nFileError ; 

int StateSav_ReadAtariState(const char *filename, const char *mode)
{
	char header_string[8];
	UBYTE StateVersion = 0;  /* The version of the save file */
	UBYTE SaveVerbose = 0;   /* Verbose mode means save basic, OS if patched */

	if (StateFile != NULL) {
		GZCLOSE(StateFile);
		StateFile = NULL;
	}
	nFileError = Z_OK;

	StateFile = GZOPEN(filename, mode);
	if (StateFile == NULL) {
		Log_print("Could not open %s for state read.", filename);
		GetGZErrorText();
		return FALSE;
	}

	if (GZREAD(StateFile, header_string, 8) == 0) {
		GetGZErrorText();
		GZCLOSE(StateFile);
		StateFile = NULL;
		return FALSE;
	}
	if (memcmp(header_string, "ATARI800", 8) != 0) {
		Log_print("This is not an Atari800 state save file.");
		GZCLOSE(StateFile);
		StateFile = NULL;
		return FALSE;
	}

	if (GZREAD(StateFile, &StateVersion, 1) == 0
	 || GZREAD(StateFile, &SaveVerbose, 1) == 0) {
		Log_print("Failed read from Atari state file.");
		GetGZErrorText();
		GZCLOSE(StateFile);
		StateFile = NULL;
		return FALSE;
	}

	if (StateVersion > SAVE_VERSION_NUMBER || StateVersion < 3) {
		Log_print("Cannot read this state file because it is an incompatible version.");
		GZCLOSE(StateFile);
		StateFile = NULL;
		return FALSE;
	}

	Atari800_StateRead(StateVersion);
	if (StateVersion >= 4) {
		CARTRIDGE_StateRead(StateVersion);
		SIO_StateRead();
	}
	ANTIC_StateRead();
	CPU_StateRead(SaveVerbose, StateVersion);
	GTIA_StateRead(StateVersion);
	PIA_StateRead(StateVersion);
	POKEY_StateRead();
	if (StateVersion >= 6) {
#ifdef XEP80_EMULATION
		XEP80_StateRead();
#else
		int local_xep80_enabled;
		StateSav_ReadINT(&local_xep80_enabled,1);
		if (local_xep80_enabled) {
			Log_print("Cannot read this state file because this version does not support XEP80.");
			GZCLOSE(StateFile);
			StateFile = NULL;
			return FALSE;
		}
#endif /* XEP80_EMULATION */
		PBI_StateRead();
#ifdef PBI_MIO
		PBI_MIO_StateRead();
#else
		{
			int local_mio_enabled;
			StateSav_ReadINT(&local_mio_enabled,1);
			if (local_mio_enabled) {
				Log_print("Cannot read this state file because this version does not support MIO.");
				GZCLOSE(StateFile);
				StateFile = NULL;
				return FALSE;
			}
		}
#endif /* PBI_MIO */
#ifdef PBI_BB
		PBI_BB_StateRead();
#else
		{
			int local_bb_enabled;
			StateSav_ReadINT(&local_bb_enabled,1);
			if (local_bb_enabled) {
				Log_print("Cannot read this state file because this version does not support the Black Box.");
				GZCLOSE(StateFile);
				StateFile = NULL;
				return FALSE;
			}
		}
#endif /* PBI_BB */
#ifdef PBI_XLD
		PBI_XLD_StateRead();
#else
		{
			int local_xld_enabled;
			StateSav_ReadINT(&local_xld_enabled,1);
			if (local_xld_enabled) {
				Log_print("Cannot read this state file because this version does not support the 1400XL/1450XLD.");
				GZCLOSE(StateFile);
				StateFile = NULL;
				return FALSE;
			}
		}
#endif /* PBI_XLD */
	}
#ifdef DREAMCAST
	DCStateRead();
#endif

	GZCLOSE(StateFile);
	StateFile = NULL;

	if (nFileError != Z_OK)
		return FALSE;

	return TRUE;
}