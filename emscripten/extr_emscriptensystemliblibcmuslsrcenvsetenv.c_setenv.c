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
 int /*<<< orphan*/  __putenv (char*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getenv (char const*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ strchr (char const*,char) ; 
 int strlen (char const*) ; 

int setenv(const char *var, const char *value, int overwrite)
{
	char *s;
	int l1, l2;

	if (!var || !*var || strchr(var, '=')) {
		errno = EINVAL;
		return -1;
	}
	if (!overwrite && getenv(var)) return 0;

	l1 = strlen(var);
	l2 = strlen(value);
	s = malloc(l1+l2+2);
	if (s) {
		memcpy(s, var, l1);
		s[l1] = '=';
		memcpy(s+l1+1, value, l2);
		s[l1+l2+1] = 0;
		if (!__putenv(s, 1)) return 0;
	}
	free(s);
	return -1;
}