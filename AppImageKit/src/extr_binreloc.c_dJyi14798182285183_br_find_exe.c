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
 char* exe ; 
 char* strdup (char const*) ; 

char *
br_find_exe (const char *default_exe)
{
	if (exe == (char *) NULL) {
		/* BinReloc is not initialized. */
		if (default_exe != (const char *) NULL)
			return strdup (default_exe);
		else
			return (char *) NULL;
	}
	return strdup (exe);
}