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
 char* find_tracing_dir () ; 
 char* malloc_or_die (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *get_tracing_file(const char *name)
{
	const char *tracing;
	char *file;

	tracing = find_tracing_dir();
	if (!tracing)
		return NULL;

	file = malloc_or_die(strlen(tracing) + strlen(name) + 2);

	sprintf(file, "%s/%s", tracing, name);
	return file;
}