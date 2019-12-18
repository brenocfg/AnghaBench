#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* hue; void* gamma; void* brightness; void* contrast; void* saturation; } ;

/* Variables and functions */
 int /*<<< orphan*/  Atari800_tv_mode ; 
 int CFG_MatchTextParameter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COLOURS_NTSC_Initialise (int*,char**) ; 
 int /*<<< orphan*/  COLOURS_NTSC_RestoreDefaults () ; 
 TYPE_1__ COLOURS_NTSC_setup ; 
 int /*<<< orphan*/  COLOURS_PAL_Initialise (int*,char**) ; 
 int /*<<< orphan*/  COLOURS_PAL_RestoreDefaults () ; 
 TYPE_1__ COLOURS_PAL_setup ; 
 int /*<<< orphan*/  COLOURS_PRESET_SIZE ; 
 int FALSE ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int TRUE ; 
 int /*<<< orphan*/  UpdateModeDependentPointers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdatePalette () ; 
 void* atof (char*) ; 
 int /*<<< orphan*/  preset_cfg_strings ; 
 TYPE_1__* presets ; 
 scalar_t__ strcmp (char*,char*) ; 

int Colours_Initialise(int *argc, char *argv[])
{
	int i;
	int j;

	for (i = j = 1; i < *argc; i++) {
		int i_a = (i + 1 < *argc);		/* is argument available? */
		int a_m = FALSE;			/* error, argument missing! */
		
		if (strcmp(argv[i], "-saturation") == 0) {
			if (i_a)
				COLOURS_NTSC_setup.saturation = COLOURS_PAL_setup.saturation = atof(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-contrast") == 0) {
			if (i_a)
				COLOURS_NTSC_setup.contrast = COLOURS_PAL_setup.contrast = atof(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-brightness") == 0) {
			if (i_a)
				COLOURS_NTSC_setup.brightness = COLOURS_PAL_setup.brightness = atof(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-gamma") == 0) {
			if (i_a)
				COLOURS_NTSC_setup.gamma = COLOURS_PAL_setup.gamma = atof(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-tint") == 0) {
			if (i_a)
				COLOURS_NTSC_setup.hue = COLOURS_PAL_setup.hue = atof(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-colors-preset") == 0) {
			if (i_a) {
				int idx = CFG_MatchTextParameter(argv[++i], preset_cfg_strings, COLOURS_PRESET_SIZE);
				if (idx < 0) {
					Log_print("Invalid value for -colors-preset");
					return FALSE;
				}
				COLOURS_NTSC_setup = COLOURS_PAL_setup = presets[idx];
				COLOURS_NTSC_RestoreDefaults();
				COLOURS_PAL_RestoreDefaults();
			} else a_m = TRUE;
		}

		else {
			if (strcmp(argv[i], "-help") == 0) {
				Log_print("\t-colors-preset standard|deep-black|vibrant");
				Log_print("\t                       Use one of predefined color adjustments");
				Log_print("\t-saturation <num>      Set color saturation");
				Log_print("\t-contrast <num>        Set contrast");
				Log_print("\t-brightness <num>      Set brightness");
				Log_print("\t-gamma <num>           Set color gamma factor");
				Log_print("\t-tint <num>            Set tint");
			}
			argv[j++] = argv[i];
		}

		if (a_m) {
			Log_print("Missing argument for '%s'", argv[i]);
			return FALSE;
		}
	}
	*argc = j;

	if (!COLOURS_NTSC_Initialise(argc, argv) ||
	    !COLOURS_PAL_Initialise(argc, argv))
		return FALSE;

	/* Assume that Atari800_tv_mode has been already initialised. */
	UpdateModeDependentPointers(Atari800_tv_mode);
	UpdatePalette();
	return TRUE;
}