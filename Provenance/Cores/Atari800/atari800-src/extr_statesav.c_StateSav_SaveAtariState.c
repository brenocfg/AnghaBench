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
 int /*<<< orphan*/  ANTIC_StateSave () ; 
 int /*<<< orphan*/  Atari800_StateSave () ; 
 int /*<<< orphan*/  CARTRIDGE_StateSave () ; 
 int /*<<< orphan*/  CPU_StateSave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCStateSave () ; 
 int FALSE ; 
 int /*<<< orphan*/  GTIA_StateSave () ; 
 scalar_t__ GZCLOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GZOPEN (char const*,char const*) ; 
 scalar_t__ GZWRITE (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  GetGZErrorText () ; 
 int /*<<< orphan*/  Log_print (char*,char const*) ; 
 int /*<<< orphan*/  PBI_BB_StateSave () ; 
 int /*<<< orphan*/  PBI_MIO_StateSave () ; 
 int /*<<< orphan*/  PBI_StateSave () ; 
 int /*<<< orphan*/  PBI_XLD_StateSave () ; 
 int /*<<< orphan*/  PIA_StateSave () ; 
 int /*<<< orphan*/  POKEY_StateSave () ; 
 int /*<<< orphan*/  SAVE_VERSION_NUMBER ; 
 int /*<<< orphan*/  SIO_StateSave () ; 
 int /*<<< orphan*/ * StateFile ; 
 int /*<<< orphan*/  StateSav_SaveINT (int*,int) ; 
 int /*<<< orphan*/  StateSav_SaveUBYTE (int /*<<< orphan*/ *,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  XEP80_StateSave () ; 
 scalar_t__ Z_OK ; 
 scalar_t__ nFileError ; 

int StateSav_SaveAtariState(const char *filename, const char *mode, UBYTE SaveVerbose)
{
	UBYTE StateVersion = SAVE_VERSION_NUMBER;

	if (StateFile != NULL) {
		GZCLOSE(StateFile);
		StateFile = NULL;
	}
	nFileError = Z_OK;

	StateFile = GZOPEN(filename, mode);
	if (StateFile == NULL) {
		Log_print("Could not open %s for state save.", filename);
		GetGZErrorText();
		return FALSE;
	}
	if (GZWRITE(StateFile, "ATARI800", 8) == 0) {
		GetGZErrorText();
		GZCLOSE(StateFile);
		StateFile = NULL;
		return FALSE;
	}

	StateSav_SaveUBYTE(&StateVersion, 1);
	StateSav_SaveUBYTE(&SaveVerbose, 1);
	/* The order here is important. Atari800_StateSave must be first because it saves the machine type, and
	   decisions on what to save/not save are made based off that later in the process */
	Atari800_StateSave();
	CARTRIDGE_StateSave();
	SIO_StateSave();
	ANTIC_StateSave();
	CPU_StateSave(SaveVerbose);
	GTIA_StateSave();
	PIA_StateSave();
	POKEY_StateSave();
#ifdef XEP80_EMULATION
	XEP80_StateSave();
#else
	{
		int local_xep80_enabled = FALSE;
		StateSav_SaveINT(&local_xep80_enabled, 1);
	}
#endif /* XEP80_EMULATION */
	PBI_StateSave();
#ifdef PBI_MIO
	PBI_MIO_StateSave();
#else
	{
		int local_mio_enabled = FALSE;
		StateSav_SaveINT(&local_mio_enabled, 1);
	}
#endif /* PBI_MIO */
#ifdef PBI_BB
	PBI_BB_StateSave();
#else
	{
		int local_bb_enabled = FALSE;
		StateSav_SaveINT(&local_bb_enabled, 1);
	}
#endif /* PBI_BB */
#ifdef PBI_XLD
	PBI_XLD_StateSave();
#else
	{
		int local_xld_enabled = FALSE;
		StateSav_SaveINT(&local_xld_enabled, 1);
	}
#endif /* PBI_XLD */
#ifdef DREAMCAST
	DCStateSave();
#endif

	if (GZCLOSE(StateFile) != 0) {
		StateFile = NULL;
		return FALSE;
	}
	StateFile = NULL;

	if (nFileError != Z_OK)
		return FALSE;

	return TRUE;
}