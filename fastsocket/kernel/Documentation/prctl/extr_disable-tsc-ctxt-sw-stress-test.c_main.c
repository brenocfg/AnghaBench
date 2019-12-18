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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rdtsctask () ; 
 int /*<<< orphan*/  segvtask () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
	int n_tasks = 100, i;

	fprintf(stderr, "[No further output means we're allright]\n");

	for (i=0; i<n_tasks; i++)
		if (fork() == 0)
		{
			if (i & 1)
				segvtask();
			else
				rdtsctask();
		}

	for (i=0; i<n_tasks; i++)
		wait(NULL);

	exit(0);
}