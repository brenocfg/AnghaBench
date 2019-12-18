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
 int /*<<< orphan*/  EINVAL ; 
 char** environ ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ findenv (char const*,int*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

int
unsetenv(const char *name)
{
	char **p;
	int offset;

	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL) {
		errno = EINVAL;
		return -1;
	}

	while (findenv(name, &offset))	{ /* if set multiple times */
		for (p = &environ[offset];; ++p)
			if (!(*p = *(p + 1)))
				break;
	}
	return 0;
}