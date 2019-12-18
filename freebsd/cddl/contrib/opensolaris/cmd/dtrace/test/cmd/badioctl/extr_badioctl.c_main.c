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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  WEXITED ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  badioctl (scalar_t__) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

int
main()
{
	pid_t child, parent = getpid();
	int status;

	for (;;) {
		if ((child = fork()) == 0)
			badioctl(parent);

		while (waitpid(child, &status, WEXITED) != child)
			continue;

		if (WIFEXITED(status)) {
			/*
			 * Our child exited by design -- we'll exit with
			 * the same status code.
			 */
			exit(WEXITSTATUS(status));
		}

		/*
		 * Our child died on a signal.  Respawn it.
		 */
		printf("badioctl: child died on signal %d; respawning.\n",
		    WTERMSIG(status));
		fflush(stdout);
	}

	/* NOTREACHED */
	return (0);
}