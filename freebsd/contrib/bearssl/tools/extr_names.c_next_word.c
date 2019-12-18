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
 scalar_t__ is_ign (char const) ; 

__attribute__((used)) static const char *
next_word(const char **str, size_t *len)
{
	int c;
	const char *begin;
	size_t u;

	/*
	 * Find next non-ignored character which is not a comma.
	 */
	for (;;) {
		c = **str;
		if (c == 0) {
			*len = 0;
			return NULL;
		}
		if (!is_ign(c) && c != ',') {
			break;
		}
		(*str) ++;
	}

	/*
	 * Find next comma or terminator.
	 */
	begin = *str;
	for (;;) {
		c = *(*str);
		if (c == 0 || c == ',') {
			break;
		}
		(*str) ++;
	}

	/*
	 * Remove trailing ignored characters.
	 */
	u = (size_t)(*str - begin);
	while (u > 0 && is_ign(begin[u - 1])) {
		u --;
	}
	if (c == ',') {
		(*str) ++;
	}
	*len = u;
	return begin;
}