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

__attribute__((used)) static char *
range_match(char *pattern, int test)
{
	char c;
	char c2;
	int negate;
	int ok = 0;

	if ((negate = (*pattern == '!')) != 0)
		++pattern;

	while ((c = *pattern++) != ']') {
		/*
		 * Illegal pattern
		 */
		if (c == '\0')
			return (NULL);

		if ((*pattern == '-') && ((c2 = pattern[1]) != '\0') &&
		    (c2 != ']')) {
			if ((c <= test) && (test <= c2))
				ok = 1;
			pattern += 2;
		} else if (c == test)
			ok = 1;
	}
	return (ok == negate ? NULL : pattern);
}