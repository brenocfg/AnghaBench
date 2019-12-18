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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int PATH_MAX ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char*,char*) ; 
 char* strdup (char*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static bool lookup_path(char *name)
{
	bool found = false;
	char *path, *tmp;
	char buf[PATH_MAX];
	char *env = getenv("PATH");

	if (!env)
		return false;

	env = strdup(env);
	if (!env)
		return false;

	path = strtok_r(env, ":", &tmp);
	while (path) {
		scnprintf(buf, sizeof(buf), "%s/%s", path, name);
		if (access(buf, F_OK) == 0) {
			found = true;
			break;
		}
		path = strtok_r(NULL, ":", &tmp);
	}
	free(env);
	return found;
}