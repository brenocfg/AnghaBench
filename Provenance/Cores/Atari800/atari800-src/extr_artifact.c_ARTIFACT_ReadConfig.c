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
 int ANTIC_artif_mode ; 
 int /*<<< orphan*/  ARTIFACT_SIZE ; 
 int CFG_MatchTextParameter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 
 int Util_sscandec (char*) ; 
 int /*<<< orphan*/  mode_cfg_strings ; 
 int mode_ntsc ; 
 int mode_pal ; 
 scalar_t__ strcmp (char*,char*) ; 

int ARTIFACT_ReadConfig(char *option, char *ptr)
{
	if (strcmp(option, "ARTIFACT_NTSC") == 0) {
		int i = CFG_MatchTextParameter(ptr, mode_cfg_strings, ARTIFACT_SIZE);
		if (i < 0)
			return FALSE;
		mode_ntsc = i;
	}
	else if (strcmp(option, "ARTIFACT_PAL") == 0) {
		int i = CFG_MatchTextParameter(ptr, mode_cfg_strings, ARTIFACT_SIZE);
		if (i < 0)
			return FALSE;
		mode_pal = i;
	}
	else if (strcmp(option, "ARTIFACT_NTSC_MODE") == 0) {
		int i = Util_sscandec(ptr);
		if (i < 0 || i > 4)
			return FALSE;
		ANTIC_artif_mode = i;
	}
	else
		return FALSE;
	return TRUE;
}