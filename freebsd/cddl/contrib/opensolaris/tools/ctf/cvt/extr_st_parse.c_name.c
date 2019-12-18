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
 scalar_t__ isalnum (char) ; 
 scalar_t__ isalpha (char) ; 
 int /*<<< orphan*/  reset () ; 
 scalar_t__ strchr (char*,char) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static char *
name(char *cp, char **w)
{
	char *new, *orig, c;
	int len;

	orig = cp;
	c = *cp++;
	if (c == ':')
		*w = NULL;
	else if (isalpha(c) || strchr("_.$#", c)) {
		for (c = *cp++; isalnum(c) || strchr(" _.$#", c); c = *cp++)
			;
		if (c != ':')
			reset();
		len = cp - orig;
		new = xmalloc(len);
		while (orig < cp - 1)
			*new++ = *orig++;
		*new = '\0';
		*w = new - (len - 1);
	} else
		reset();

	return (cp);
}