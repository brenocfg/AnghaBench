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
 char** environ ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static char *
findenv(const char *name, int *offset)
{
	size_t i, len;
	char *p, *q;

	len = strlen(name);
	for (i = 0; (q = environ[i]); i++) {
		p = strchr(q, '=');
		if (p == NULL || p - q != len)
			continue;
		if (strncmp(name, q, len) == 0) {
			*offset = i;
			return q + len + 1;
		}
	}
	*offset = i;
	return NULL;
}