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
struct TYPE_2__ {char* sharpness; char* resolution; char* artifacts; char* fringing; char* bleed; char* burst_phase; } ;

/* Variables and functions */
 int CFG_MatchTextParameter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  FILTER_NTSC_PRESET_SIZE ; 
 int /*<<< orphan*/  FILTER_NTSC_SetPreset (int) ; 
 TYPE_1__ FILTER_NTSC_setup ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int TRUE ; 
 void* atof (char*) ; 
 int /*<<< orphan*/  preset_cfg_strings ; 
 scalar_t__ strcmp (char*,char*) ; 

int FILTER_NTSC_Initialise(int *argc, char *argv[])
{
	int i;
	int j;

	for (i = j = 1; i < *argc; i++) {
		int i_a = (i + 1 < *argc);		/* is argument available? */
		int a_m = FALSE;			/* error, argument missing! */
		
		if (strcmp(argv[i], "-ntsc-sharpness") == 0) {
			if (i_a)
				FILTER_NTSC_setup.sharpness = atof(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-ntsc-resolution") == 0) {
			if (i_a)
				FILTER_NTSC_setup.resolution = atof(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-ntsc-artifacts") == 0) {
			if (i_a)
				FILTER_NTSC_setup.artifacts = atof(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-ntsc-fringing") == 0) {
			if (i_a)
				FILTER_NTSC_setup.fringing = atof(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-ntsc-bleed") == 0) {
			if (i_a)
				FILTER_NTSC_setup.bleed = atof(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-ntsc-burstphase") == 0) {
			if (i_a)
				FILTER_NTSC_setup.burst_phase = atof(argv[++i]);
			else a_m = TRUE;
		}
		else if (strcmp(argv[i], "-ntsc-filter-preset") == 0) {
			if (i_a) {
				int idx = CFG_MatchTextParameter(argv[++i], preset_cfg_strings, FILTER_NTSC_PRESET_SIZE);
				if (idx < 0) {
					Log_print("Invalid value for -ntsc-filter-preset");
					return FALSE;
				}
				FILTER_NTSC_SetPreset(idx);
			} else a_m = TRUE;
		}
		else {
			if (strcmp(argv[i], "-help") == 0) {
				Log_print("\t-ntsc-sharpness <n>   Set sharpness for NTSC filter (default %.2g)", FILTER_NTSC_setup.sharpness);
				Log_print("\t-ntsc-resolution <n>  Set resolution for NTSC filter (default %.2g)", FILTER_NTSC_setup.resolution);
				Log_print("\t-ntsc-artifacts <n>   Set luma artifacts ratio for NTSC filter (default %.2g)", FILTER_NTSC_setup.artifacts);
				Log_print("\t-ntsc-fringing <n>    Set chroma fringing ratio for NTSC filter (default %.2g)", FILTER_NTSC_setup.fringing);
				Log_print("\t-ntsc-bleed <n>       Set bleed for NTSC filter (default %.2g)", FILTER_NTSC_setup.bleed);
				Log_print("\t-ntsc-burstphase <n>  Set burst phase (artifact colours) for NTSC filter (default %.2g)", FILTER_NTSC_setup.burst_phase);
				Log_print("\t-ntsc-filter-preset composite|svideo|rgb|monochrome");
				Log_print("\t                      Use one of predefined NTSC filter adjustments");
			}
			argv[j++] = argv[i];
		}

		if (a_m) {
			Log_print("Missing argument for '%s'", argv[i]);
			return FALSE;
		}
	}
	*argc = j;

	return TRUE;
}