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
 int FALSE ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int TRUE ; 
 int VOICEBOX_enabled ; 
 int VOICEBOX_ii ; 
 scalar_t__ strcmp (char*,char*) ; 

int VOICEBOX_Initialise(int *argc, char *argv[])
{
	int i, j;
	for (i = j = 1; i < *argc; i++) {
		if (strcmp(argv[i], "-voicebox") == 0) {
			VOICEBOX_enabled = TRUE;
			VOICEBOX_ii = FALSE;
		}
		else if (strcmp(argv[i], "-voiceboxii") == 0){
			VOICEBOX_enabled = TRUE;
			VOICEBOX_ii = TRUE;
		}
		else {
		 	if (strcmp(argv[i], "-help") == 0) {
				Log_print("\t-voicebox        Emulate the Alien Group Voice Box I");
				Log_print("\t-voiceboxii      Emulate the Alien Group Voice Box II");
			}

			argv[j++] = argv[i];
		}

	}
	*argc = j;

	return TRUE;
}