#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {char* mailname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_NAME_MAX ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ gethostname (char*,int) ; 
 scalar_t__ isalnum (char) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ strchr (char*,char) ; 

const char *
hostname(void)
{
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX	255
#endif
	static char name[HOST_NAME_MAX+1];
	static int initialized = 0;
	char *s;

	if (initialized)
		return (name);

	if (config.mailname == NULL || !*config.mailname)
		goto local;

	if (config.mailname[0] == '/') {
		/*
		 * If the mailname looks like an absolute path,
		 * treat it as a file.
		 */
		FILE *fp;

		fp = fopen(config.mailname, "r");
		if (fp == NULL)
			goto local;

		s = fgets(name, sizeof(name), fp);
		fclose(fp);
		if (s == NULL)
			goto local;

		for (s = name; *s != 0 && (isalnum(*s) || strchr("_.-", *s)); ++s)
			/* NOTHING */;
		*s = 0;

		if (!*name)
			goto local;

		initialized = 1;
		return (name);
	} else {
		snprintf(name, sizeof(name), "%s", config.mailname);
		initialized = 1;
		return (name);
	}

local:
	if (gethostname(name, sizeof(name)) != 0)
		*name = 0;
	/*
	 * gethostname() is allowed to truncate name without NUL-termination
	 * and at the same time not return an error.
	 */
	name[sizeof(name) - 1] = 0;

	for (s = name; *s != 0 && (isalnum(*s) || strchr("_.-", *s)); ++s)
		/* NOTHING */;
	*s = 0;

	if (!*name)
		snprintf(name, sizeof(name), "unknown-hostname");

	initialized = 1;
	return (name);
}