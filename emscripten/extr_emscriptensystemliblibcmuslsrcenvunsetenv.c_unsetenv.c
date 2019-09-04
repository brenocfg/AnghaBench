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
 char** __env_map ; 
 char** __environ ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memcmp (char const*,char*,size_t) ; 
 scalar_t__ strchr (char const*,char) ; 
 size_t strlen (char const*) ; 

int unsetenv(const char *name)
{
	int i, j;
	size_t l = strlen(name);

	if (!*name || strchr(name, '=')) {
		errno = EINVAL;
		return -1;
	}
again:
	for (i=0; __environ[i] && (memcmp(name, __environ[i], l) || __environ[i][l] != '='); i++);
	if (__environ[i]) {
		if (__env_map) {
			for (j=0; __env_map[j] && __env_map[j] != __environ[i]; j++);
			free (__env_map[j]);
			for (; __env_map[j]; j++)
				__env_map[j] = __env_map[j+1];
		}
		for (; __environ[i]; i++)
			__environ[i] = __environ[i+1];
		goto again;
	}
	return 0;
}