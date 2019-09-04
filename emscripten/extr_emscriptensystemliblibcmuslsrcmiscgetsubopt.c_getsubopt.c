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
 char* strchr (char*,char) ; 
 size_t strlen (char* const) ; 
 scalar_t__ strncmp (char* const,char*,size_t) ; 

int getsubopt(char **opt, char *const *keys, char **val)
{
	char *s = *opt;
	int i;

	*val = NULL;
	*opt = strchr(s, ',');
	if (*opt) *(*opt)++ = 0;
	else *opt = s + strlen(s);

	for (i=0; keys[i]; i++) {
		size_t l = strlen(keys[i]);
		if (strncmp(keys[i], s, l)) continue;
		if (s[l] == '=')
			*val = s + l + 1;
		else if (s[l]) continue;
		return i;
	}
	return -1;
}