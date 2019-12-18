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
struct buildid_dir_config {char* dir; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 char* perf_config_dirname (char const*,char const*) ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int buildid_dir_command_config(const char *var, const char *value,
				      void *data)
{
	struct buildid_dir_config *c = data;
	const char *v;

	/* same dir for all commands */
	if (!prefixcmp(var, "buildid.") && !strcmp(var + 8, "dir")) {
		v = perf_config_dirname(var, value);
		if (!v)
			return -1;
		strncpy(c->dir, v, MAXPATHLEN-1);
		c->dir[MAXPATHLEN-1] = '\0';
	}
	return 0;
}