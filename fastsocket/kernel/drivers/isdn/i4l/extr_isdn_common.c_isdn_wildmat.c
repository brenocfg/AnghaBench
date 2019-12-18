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
 int isdn_star (char*,char*) ; 

__attribute__((used)) static int
isdn_wildmat(char *s, char *p)
{
	register int last;
	register int matched;
	register int reverse;
	register int nostar = 1;

	if (!(*s) && !(*p))
		return(1);
	for (; *p; s++, p++)
		switch (*p) {
			case '\\':
				/*
				 * Literal match with following character,
				 * fall through.
				 */
				p++;
			default:
				if (*s != *p)
					return (*s == '\0')?2:1;
				continue;
			case '?':
				/* Match anything. */
				if (*s == '\0')
					return (2);
				continue;
			case '*':
				nostar = 0;	
				/* Trailing star matches everything. */
				return (*++p ? isdn_star(s, p) : 0);
			case '[':
				/* [^....] means inverse character class. */
				if ((reverse = (p[1] == '^')))
					p++;
				for (last = 0, matched = 0; *++p && (*p != ']'); last = *p)
					/* This next line requires a good C compiler. */
					if (*p == '-' ? *s <= *++p && *s >= last : *s == *p)
						matched = 1;
				if (matched == reverse)
					return (1);
				continue;
		}
	return (*s == '\0')?0:nostar;
}