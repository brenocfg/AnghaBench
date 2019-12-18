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
 char* find_debugfs () ; 
 char* malloc_or_die (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static const char *find_tracing_dir(void)
{
	static char *tracing;
	static int tracing_found;
	const char *debugfs;

	if (tracing_found)
		return tracing;

	debugfs = find_debugfs();

	tracing = malloc_or_die(strlen(debugfs) + 9);

	sprintf(tracing, "%s/tracing", debugfs);

	tracing_found = 1;
	return tracing;
}