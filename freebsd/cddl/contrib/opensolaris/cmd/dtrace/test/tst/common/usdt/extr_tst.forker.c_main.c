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
 int /*<<< orphan*/  FORKER_FIRE () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ *) ; 

int
main(int argc, char **argv)
{
	int i;

	for (i = 0; i < 10000; i++) {
		FORKER_FIRE();
		if (fork() == 0)
			exit(0);

		(void) wait(NULL);
	}

	return (0);
}