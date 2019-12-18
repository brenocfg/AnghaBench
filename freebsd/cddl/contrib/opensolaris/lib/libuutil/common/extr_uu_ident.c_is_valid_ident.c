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
 scalar_t__ IS_ALPHA (char) ; 
 scalar_t__ IS_DIGIT (char) ; 

__attribute__((used)) static int
is_valid_ident(const char *s, const char *e, int allowdot)
{
	char c;

	if (s >= e)
		return (0);		/* name is empty */

	c = *s++;
	if (!IS_ALPHA(c))
		return (0);		/* does not start with letter */

	while (s < e && (c = *s++) != 0) {
		if (IS_ALPHA(c) || IS_DIGIT(c) || c == '-' || c == '_' ||
		    (allowdot && c == '.'))
			continue;
		return (0);		/* invalid character */
	}
	return (1);
}