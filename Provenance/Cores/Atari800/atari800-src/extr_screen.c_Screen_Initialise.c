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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int /*<<< orphan*/  Screen_EntireDirty () ; 
 int Screen_HEIGHT ; 
 int /*<<< orphan*/  Screen_SetScreenshotFilenamePattern (char*) ; 
 int Screen_WIDTH ; 
 int /*<<< orphan*/ * Screen_atari ; 
 int /*<<< orphan*/ * Screen_atari1 ; 
 int /*<<< orphan*/ * Screen_atari2 ; 
 int /*<<< orphan*/ * Screen_atari_b ; 
 int /*<<< orphan*/ * Screen_dirty ; 
 int Screen_show_atari_speed ; 
 int TRUE ; 
 scalar_t__ Util_malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

int Screen_Initialise(int *argc, char *argv[])
{
	int i;
	int j;
	int help_only = FALSE;

	for (i = j = 1; i < *argc; i++) {
		int i_a = (i + 1 < *argc);		/* is argument available? */
		int a_m = FALSE;			/* error, argument missing! */
		
		if (strcmp(argv[i], "-screenshots") == 0) {
			if (i_a)
				Screen_SetScreenshotFilenamePattern(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-showspeed") == 0) {
			Screen_show_atari_speed = TRUE;
		}
		else {
			if (strcmp(argv[i], "-help") == 0) {
				help_only = TRUE;
				Log_print("\t-screenshots <p> Set filename pattern for screenshots");
				Log_print("\t-showspeed       Show percentage of actual speed");
			}
			argv[j++] = argv[i];
		}

		if (a_m) {
			Log_print("Missing argument for '%s'", argv[i]);
			return FALSE;
		}
	}
	*argc = j;

	/* don't bother mallocing Screen_atari with just "-help" */
	if (help_only)
		return TRUE;

	if (Screen_atari == NULL) { /* platform-specific code can initialize it in theory */
		Screen_atari = (ULONG *) Util_malloc(Screen_HEIGHT * Screen_WIDTH);
		/* Clear the screen. */
		memset(Screen_atari, 0, Screen_HEIGHT * Screen_WIDTH);
#ifdef DIRTYRECT
		Screen_dirty = (UBYTE *) Util_malloc(Screen_HEIGHT * Screen_WIDTH / 8);
		Screen_EntireDirty();
#endif
#ifdef BITPL_SCR
		Screen_atari_b = (ULONG *) Util_malloc(Screen_HEIGHT * Screen_WIDTH);
		memset(Screen_atari_b, 0, Screen_HEIGHT * Screen_WIDTH);
		Screen_atari1 = Screen_atari;
		Screen_atari2 = Screen_atari_b;
#endif
	}

	return TRUE;
}