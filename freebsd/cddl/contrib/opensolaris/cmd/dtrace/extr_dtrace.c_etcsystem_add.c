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
typedef  int /*<<< orphan*/  mods ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int dtrace_provider_modules (int /*<<< orphan*/ ,char const**,int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_dtp ; 
 char const** g_etc ; 
 char const* g_etcbegin ; 
 char const* g_etcend ; 
 int /*<<< orphan*/  g_etcfile ; 
 int /*<<< orphan*/  g_ofile ; 
 int /*<<< orphan*/ * g_ofp ; 
 int /*<<< orphan*/  oprintf (char*,char const*) ; 

__attribute__((used)) static void
etcsystem_add(void)
{
	const char *mods[20];
	int nmods, line;

	if ((g_ofp = fopen(g_ofile = g_etcfile, "a")) == NULL)
		fatal("failed to open output file '%s'", g_ofile);

	oprintf("%s\n", g_etcbegin);

	for (line = 0; g_etc[line] != NULL; line++)
		oprintf("%s\n", g_etc[line]);

	nmods = dtrace_provider_modules(g_dtp, mods,
	    sizeof (mods) / sizeof (char *) - 1);

	if (nmods >= sizeof (mods) / sizeof (char *))
		fatal("unexpectedly large number of modules!");

	mods[nmods++] = "dtrace";

	for (line = 0; line < nmods; line++)
		oprintf("forceload: drv/%s\n", mods[line]);

	oprintf("%s\n", g_etcend);

	if (fclose(g_ofp) == EOF)
		fatal("failed to close output file '%s'", g_ofile);

	error("added forceload directives to %s\n", g_ofile);
}