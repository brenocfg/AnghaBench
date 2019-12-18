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
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 int strlen (char*) ; 

char *
strhyphenate(char *s)
{
	char *p, *q;

	for (p = s, q = p + strlen(p); p < q; p++) {
		if (p[0] == '_' && p[1] == '_') {
			p[0] = '-';
			bcopy(p + 2, p + 1, (size_t)(q - p) - 1);
		}
	}

	return (s);
}