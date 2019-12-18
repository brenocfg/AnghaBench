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
 int MAX_SETUP_ARGS ; 
 char** setup_args ; 
 int* setup_used ; 
 int simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int
check_setup_args(char *key, int *flags, int *val, char *buf)
{
	int x;
	char *cp;

	for (x = 0; x < MAX_SETUP_ARGS; x++) {
		if (setup_used[x])
			continue;
		if (!strncmp(setup_args[x], key, strlen(key)))
			break;
		if (!strncmp(setup_args[x], "next", strlen("next")))
			return 0;
	}
	if (x == MAX_SETUP_ARGS)
		return 0;
	setup_used[x] = 1;
	cp = setup_args[x] + strlen(key);
	*val = -1;
	if (*cp != ':')
		return ++x;
	cp++;
	if ((*cp >= '0') && (*cp <= '9')) {
		*val = simple_strtoul(cp, NULL, 0);
	}
	return ++x;
}