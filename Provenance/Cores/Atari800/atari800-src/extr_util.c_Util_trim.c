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
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int strlen (char*) ; 

void Util_trim(char *s)
{
	char *p = s;
	char *q;
	/* skip leading whitespace */
	while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')
		p++;
	/* now p points at the first non-whitespace character */

	if (*p == '\0') {
		/* only whitespace */
		*s = '\0';
		return;
	}

	q = s + strlen(s);
	/* skip trailing whitespace */
	/* we have found p < q such that *p is non-whitespace,
	   so this loop terminates with q >= p */
	do
		q--;
	while (*q == ' ' || *q == '\t' || *q == '\r' || *q == '\n');

	/* now q points at the last non-whitespace character */
	/* cut off trailing whitespace */
	*++q = '\0';

	/* move to string */
	memmove(s, p, q + 1 - p);
}