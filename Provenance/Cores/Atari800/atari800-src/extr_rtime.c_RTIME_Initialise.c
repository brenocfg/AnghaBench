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
 int RTIME_enabled ; 
 int TRUE ; 
 scalar_t__ strcmp (char*,char*) ; 

int RTIME_Initialise(int *argc, char *argv[])
{
	int i;
	int j;
	for (i = j = 1; i < *argc; i++) {
		if (strcmp(argv[i], "-rtime") == 0)
			RTIME_enabled = TRUE;
		else if (strcmp(argv[i], "-nortime") == 0)
			RTIME_enabled = FALSE;
		else {
			if (strcmp(argv[i], "-help") == 0) {
				Log_print("\t-rtime           Enable R-Time 8 emulation");
				Log_print("\t-nortime         Disable R-Time 8 emulation");
			}
			argv[j++] = argv[i];
		}
	}
	*argc = j;

	return TRUE;
}