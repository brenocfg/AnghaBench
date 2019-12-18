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
 int /*<<< orphan*/  TRACE (char*) ; 
 int cdlogical (char*) ; 
 int cdphysical (char*) ; 
 scalar_t__ curdir ; 
 int /*<<< orphan*/  flushout (int /*<<< orphan*/ ) ; 
 scalar_t__ iflag ; 
 int /*<<< orphan*/  out1 ; 
 int /*<<< orphan*/  out1fmt (char*,scalar_t__) ; 
 int /*<<< orphan*/  outclearerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
docd(char *dest, int print, int phys)
{
	int rc;

	TRACE(("docd(\"%s\", %d, %d) called\n", dest, print, phys));

	/* If logical cd fails, fall back to physical. */
	if ((phys || (rc = cdlogical(dest)) < 0) && (rc = cdphysical(dest)) < 0)
		return (-1);

	if (print && iflag && curdir) {
		out1fmt("%s\n", curdir);
		/*
		 * Ignore write errors to preserve the invariant that the
		 * current directory is changed iff the exit status is 0
		 * (or 1 if -e was given and the full pathname could not be
		 * determined).
		 */
		flushout(out1);
		outclearerror(out1);
	}

	return (rc);
}