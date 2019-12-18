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
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int strlen (char*) ; 

char *
stresep(char **stringp, const char *delim, int esc)
{
	char *s;
	const char *spanp;
	int c, sc;
	size_t l;
	char *tok;

	if (stringp == NULL || delim == NULL)
		return NULL;

	if ((s = *stringp) == NULL)
		return NULL;
	l = strlen(s) + 1;
	for (tok = s;;) {
		c = *s++;
		l--;
		while (esc != '\0' && c == esc) {
			memmove(s - 1, s, l);
			c = *s++;
			l--;
		}
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == '\0')
					s = NULL;
				else
					s[-1] = '\0';
				*stringp = s;
				return tok;
			}
		} while (sc != '\0');
	}
}