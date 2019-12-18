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
 int TRUE ; 
 int /*<<< orphan*/  init_mio () ; 
 scalar_t__ strcmp (char*,char*) ; 

int PBI_MIO_Initialise(int *argc, char *argv[])
{
	int i, j;
	for (i = j = 1; i < *argc; i++) {
		if (strcmp(argv[i], "-mio") == 0) {
			init_mio();
		}
		else {
		 	if (strcmp(argv[i], "-help") == 0) {
				Log_print("\t-mio             Emulate the ICD MIO board");
			}
			argv[j++] = argv[i];
		}
	}
	*argc = j;

	return TRUE;
}