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
 char* strchr (char const*,int) ; 
 int strlen (char const*) ; 
 int strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int strn_pattern_cmp(const char *patt, const char *name, int wildchar)
{
	const char *p;
	int len;

	/*
	 * check for trailing wildcard: *\0
	 */
	p = strchr(patt, wildchar);
	if (p && ((*(p + 1)) == 0))
		len = p - patt;
	else {
		len = strlen(name);
		if (!len) {
			if (!*patt)
				return 0;
			return -1;
		}
	}

	return strncmp(patt, name, len);
}