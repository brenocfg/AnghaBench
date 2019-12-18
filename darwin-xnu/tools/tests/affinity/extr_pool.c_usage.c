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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage()
{
	fprintf(stderr,
		"usage: pool [-a]    Turn affinity on (off)\n"
		"            [-b B]  Number of buffers per producer (2)\n"
		"            [-i I]  Number of buffers to produce (10000)\n"
		"            [-s S]  Number of stages (2)\n"
		"            [-p P]  Number of pages per buffer (256=1MB)]\n"
		"            [-w]    Consumer writes data\n"
		"            [-v V]  Verbosity level 0..2 (1)\n"
		"            [N [M]] Number of producer and consumers (2)\n"
	);
	exit(1);
}