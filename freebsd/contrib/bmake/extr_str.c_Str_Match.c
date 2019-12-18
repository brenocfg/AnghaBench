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

int
Str_Match(const char *string, const char *pattern)
{
	char c2;

	for (;;) {
		/*
		 * See if we're at the end of both the pattern and the
		 * string. If, we succeeded.  If we're at the end of the
		 * pattern but not at the end of the string, we failed.
		 */
		if (*pattern == 0)
			return(!*string);
		if (*string == 0 && *pattern != '*')
			return(0);
		/*
		 * Check for a "*" as the next pattern character.  It matches
		 * any substring.  We handle this by calling ourselves
		 * recursively for each postfix of string, until either we
		 * match or we reach the end of the string.
		 */
		if (*pattern == '*') {
			pattern += 1;
			if (*pattern == 0)
				return(1);
			while (*string != 0) {
				if (Str_Match(string, pattern))
					return(1);
				++string;
			}
			return(0);
		}
		/*
		 * Check for a "?" as the next pattern character.  It matches
		 * any single character.
		 */
		if (*pattern == '?')
			goto thisCharOK;
		/*
		 * Check for a "[" as the next pattern character.  It is
		 * followed by a list of characters that are acceptable, or
		 * by a range (two characters separated by "-").
		 */
		if (*pattern == '[') {
			int nomatch;

			++pattern;
			if (*pattern == '^') {
				++pattern;
				nomatch = 1;
			} else
				nomatch = 0;
			for (;;) {
				if ((*pattern == ']') || (*pattern == 0)) {
					if (nomatch)
						break;
					return(0);
				}
				if (*pattern == *string)
					break;
				if (pattern[1] == '-') {
					c2 = pattern[2];
					if (c2 == 0)
						return(nomatch);
					if ((*pattern <= *string) &&
					    (c2 >= *string))
						break;
					if ((*pattern >= *string) &&
					    (c2 <= *string))
						break;
					pattern += 2;
				}
				++pattern;
			}
			if (nomatch && (*pattern != ']') && (*pattern != 0))
				return 0;
			while ((*pattern != ']') && (*pattern != 0))
				++pattern;
			goto thisCharOK;
		}
		/*
		 * If the next pattern character is '/', just strip off the
		 * '/' so we do exact matching on the character that follows.
		 */
		if (*pattern == '\\') {
			++pattern;
			if (*pattern == 0)
				return(0);
		}
		/*
		 * There's no special character.  Just make sure that the
		 * next characters of each string match.
		 */
		if (*pattern != *string)
			return(0);
thisCharOK:	++pattern;
		++string;
	}
}