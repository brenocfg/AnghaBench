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
 int /*<<< orphan*/  Log_print (char*) ; 
 int PBI_XLD_enabled ; 
 int PBI_XLD_v_enabled ; 
 int TRUE ; 
 int /*<<< orphan*/  init_xld_d () ; 
 int /*<<< orphan*/  init_xld_v () ; 
 scalar_t__ strcmp (char*,char*) ; 
 int xld_d_enabled ; 

int PBI_XLD_Initialise(int *argc, char *argv[])
{
	int i, j;
	for (i = j = 1; i < *argc; i++) {
		if (strcmp(argv[i], "-1400") == 0) {
			PBI_XLD_v_enabled = TRUE;
			PBI_XLD_enabled = TRUE;
		}else if (strcmp(argv[i], "-xld") == 0){
			PBI_XLD_v_enabled = TRUE;
			xld_d_enabled = TRUE;
			PBI_XLD_enabled = TRUE;
		}
		else {
		 	if (strcmp(argv[i], "-help") == 0) {
				Log_print("\t-1400            Emulate the Atari 1400XL");
				Log_print("\t-xld             Emulate the Atari 1450XLD");
			}

			argv[j++] = argv[i];
		}

	}
	*argc = j;

	if (PBI_XLD_v_enabled) {
		init_xld_v();
	}

	/* If you set the drive to empty in the UI, the message is displayed */
	/* If you press select, I believe it tries to slow the I/O down */
	/* in order to increase compatibility. */
	/* dskcnt6 works. dskcnt10 does not */
	if (xld_d_enabled) {
		init_xld_d();
	}

	return TRUE;
}