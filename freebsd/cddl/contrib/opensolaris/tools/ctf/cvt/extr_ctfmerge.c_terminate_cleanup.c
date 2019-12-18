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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ getenv (char*) ; 
 char* outfile ; 
 int /*<<< orphan*/  stderr ; 
 char* tmpname ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void
terminate_cleanup(void)
{
	int dounlink = getenv("CTFMERGE_TERMINATE_NO_UNLINK") ? 0 : 1;

	if (tmpname != NULL && dounlink)
		unlink(tmpname);

	if (outfile == NULL)
		return;

#if !defined(__FreeBSD__)
	if (dounlink) {
		fprintf(stderr, "Removing %s\n", outfile);
		unlink(outfile);
	}
#endif
}