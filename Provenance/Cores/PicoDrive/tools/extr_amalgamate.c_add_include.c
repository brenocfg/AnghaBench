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
typedef  int /*<<< orphan*/  processed_inc ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 char const** includes ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static const char *add_include(const char *include)
{
	int i;
	char processed_inc[128+4];

	// must first quote relative includes
	snprintf(processed_inc, sizeof(processed_inc), (include[0] != '<') ? "\"%s\"" : "%s", include);

	// find in include list
	for (i = 0; includes[i] && i < 128; i++)
	{
		if (strcmp(processed_inc, includes[i]) == 0) break;
	}
	if (i == 128) eprintf("add_include: includes overflowed\n");
	if (includes[i] != NULL)
	{
		printf("already have: %s\n", processed_inc);
		return NULL;
	}
	else
	{
		printf("adding: %s\n", processed_inc);
		includes[i] = strdup(processed_inc);
		if (includes[i] == NULL) eprintf("add_include: OOM\n");
		return includes[i];
	}
}