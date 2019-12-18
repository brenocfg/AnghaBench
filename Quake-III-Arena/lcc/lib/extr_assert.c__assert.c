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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int _assert(char *e, char *file, int line) {
	fprintf(stderr, "assertion failed:");
	if (e)
		fprintf(stderr, " %s", e);
	if (file)
		fprintf(stderr, " file %s", file);
	fprintf(stderr, " line %d\n", line);
	fflush(stderr);
	abort();
	return 0;
}