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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ xrealloc (char*,int) ; 

__attribute__((used)) static char *
slurp(FILE *fp, size_t *final_len)
{
	size_t len = 256;
	int c;
	char *l = (char *)xrealloc(NULL, len), *s = l;

	for (c = getc(fp); c != EOF; c = getc(fp)) {
		if (s == l + len) {
			l = (char *)xrealloc(l, len * 2);
			len *= 2;
		}
		*s++ = c;
	}
	if (s == l + len)
		l = (char *)xrealloc(l, len + 1);
	*s++ = '\0';

	*final_len = s - l;
	l = (char *)xrealloc(l, s - l);
	return l;
}