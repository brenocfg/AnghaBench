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
 scalar_t__ errno ; 
 scalar_t__ isalnum (int) ; 
 int /*<<< orphan*/  strtoull (char const*,char**,int /*<<< orphan*/ ) ; 

const char *
strbadidnum(const char *s)
{
	char *p;
	int c;

	if (*s == '\0')
		return (s);

	errno = 0;
	(void) strtoull(s, &p, 0);

	if (errno == 0 && *p == '\0')
		return (NULL); /* matches RGX_INT */

	while ((c = *s++) != '\0') {
		if (isalnum(c) == 0 && c != '_' && c != '`')
			return (s - 1);
	}

	return (NULL); /* matches RGX_IDENT */
}