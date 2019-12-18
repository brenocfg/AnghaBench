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
 scalar_t__ __match_charclass (char const*,char const,char const**) ; 
 scalar_t__ isspace (char const) ; 

__attribute__((used)) static bool __match_glob(const char *str, const char *pat, bool ignore_space)
{
	while (*str && *pat && *pat != '*') {
		if (ignore_space) {
			/* Ignore spaces for lazy matching */
			if (isspace(*str)) {
				str++;
				continue;
			}
			if (isspace(*pat)) {
				pat++;
				continue;
			}
		}
		if (*pat == '?') {	/* Matches any single character */
			str++;
			pat++;
			continue;
		} else if (*pat == '[')	/* Character classes/Ranges */
			if (__match_charclass(pat + 1, *str, &pat)) {
				str++;
				continue;
			} else
				return false;
		else if (*pat == '\\') /* Escaped char match as normal char */
			pat++;
		if (*str++ != *pat++)
			return false;
	}
	/* Check wild card */
	if (*pat == '*') {
		while (*pat == '*')
			pat++;
		if (!*pat)	/* Tail wild card matches all */
			return true;
		while (*str)
			if (__match_glob(str++, pat, ignore_space))
				return true;
	}
	return !*str && !*pat;
}