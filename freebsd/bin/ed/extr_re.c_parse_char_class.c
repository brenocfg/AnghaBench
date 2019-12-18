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

char *
parse_char_class(char *s)
{
	int c, d;

	if (*s == '^')
		s++;
	if (*s == ']')
		s++;
	for (; *s != ']' && *s != '\n'; s++)
		if (*s == '[' && ((d = *(s+1)) == '.' || d == ':' || d == '='))
			for (s++, c = *++s; *s != ']' || c != d; s++)
				if ((c = *s) == '\n')
					return NULL;
	return  (*s == ']') ? s : NULL;
}