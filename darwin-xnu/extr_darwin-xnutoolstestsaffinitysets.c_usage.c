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
		"usage: sets [-a]   Turn affinity on (off)\n"
		"            [-b B] Number of buffers per set/line (2)\n"
		"            [-c]   Configure for max cache performance\n"
		"            [-h]   Print this\n"
		"            [-i I] Number of items/buffers to process (1000)\n"
		"            [-s S] Number of stages per set/line (2)\n"
		"            [-t]   Halt for keyboard input to start\n"
		"            [-p P] Number of pages per buffer (256=1MB)]\n"
		"            [-w]   Consumer writes data\n"
		"            [-v V] Level of verbosity 0..2 (1)\n"
		"            [N]    Number of sets/lines (2)\n"
	);
	exit(1);
}