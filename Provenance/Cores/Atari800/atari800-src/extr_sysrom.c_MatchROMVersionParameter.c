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
 int SYSROM_AUTO ; 
 int TRUE ; 
 scalar_t__ Util_stricmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cfg_strings_rev ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int MatchROMVersionParameter(char const *string, int const *allowed_vals, int *version_ptr)
{
	if (strcmp(string, "AUTO") == 0) {
		*version_ptr = SYSROM_AUTO;
		return TRUE;
	}
	else do {
		if (Util_stricmp(string, cfg_strings_rev[*allowed_vals]) == 0) {
			*version_ptr = *allowed_vals;
			return TRUE;
		}
	} while (*++allowed_vals != -1);
	/* *string not matched to any allowed value. */
	return FALSE;
}