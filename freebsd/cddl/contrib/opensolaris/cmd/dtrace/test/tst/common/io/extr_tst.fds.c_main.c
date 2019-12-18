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
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  fds ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_NDELAY ; 
 int O_NOCTTY ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_SYNC ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  closefrom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  interrupt ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char *argv[])
{
	const char *file = "/dev/null";
	int i, n, fds[10];
	struct sigaction act;

	if (argc > 1) {
		(void) fprintf(stderr, "Usage: %s\n", argv[0]);
		return (EXIT_FAILURE);
	}

	act.sa_handler = interrupt;
	act.sa_flags = 0;

	(void) sigemptyset(&act.sa_mask);
	(void) sigaction(SIGUSR1, &act, NULL);

	closefrom(0);
	n = 0;

	/*
	 * With all of our file descriptors closed, wait here spinning in bogus
	 * ioctl() calls until DTrace hits us with a SIGUSR1 to start the test.
	 */
	if (sigsetjmp(env, 1) == 0) {
		for (;;)
			(void) ioctl(-1, 0, NULL);
	}

	/*
	 * To test the fds[] array, we open /dev/null (a file with reliable
	 * pathname and properties) using various flags and seek offsets.
	 */
	fds[n++] = open(file, O_RDONLY);
	fds[n++] = open(file, O_WRONLY);
	fds[n++] = open(file, O_RDWR);

	fds[n++] = open(file, O_RDWR | O_APPEND | O_CREAT |
	    O_NOCTTY | O_NONBLOCK | O_NDELAY | O_SYNC | O_TRUNC | 0666);

	fds[n++] = open(file, O_RDWR);
	(void) lseek(fds[n - 1], 123, SEEK_SET);

	/*
	 * Once we have all the file descriptors in the state we want to test,
	 * issue a bogus ioctl() on each fd with cmd 0 and arg NULL to whack
	 * our DTrace script into recording the content of the fds[] array.
	 */
	for (i = 0; i < n; i++)
		(void) ioctl(fds[i], 0, NULL);

	assert(n <= sizeof (fds) / sizeof (fds[0]));
	exit(0);
}