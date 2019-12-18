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
 char* curhdr ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  reset () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
_expected(
	const char *who,	/* what function, or part thereof, is reporting */
	const char *what,	/* what was expected */
	const char *where,	/* where we were in the line of input */
	int line)
{
	fprintf(stderr, "%s, expecting \"%s\" at \"%s\"\n", who, what, where);
	fprintf(stderr, "code line: %d, file %s\n", line,
	    (curhdr ? curhdr : "NO FILE"));
	reset();
}