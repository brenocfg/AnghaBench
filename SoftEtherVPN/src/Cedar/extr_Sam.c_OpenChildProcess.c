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
typedef  int PID ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ dup2 (int,int /*<<< orphan*/ ) ; 
 int execvp (char const*,char* const*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int fork () ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

PID OpenChildProcess(const char* path, char* const parameter[], int fd[] )
{
#ifdef OS_WIN32
	// not implemented
	return -1;
#else // OS_WIN32
	// UNIX
	int fds[2][2];
	PID pid;

	if (path == NULL || parameter == NULL || fd == NULL)
	{
		return (PID)-1;
	}

	if (pipe(fds[0]) != 0)
	{
		return (PID)-1;
	}

	if (pipe(fds[1]) != 0)
	{
		close(fds[0][0]);
		close(fds[0][1]);

		return (PID)-1;
	}

	pid = fork();
	if (pid == (PID)0) {
		int iError;

		close(fds[0][1]);
		close(fds[1][0]);

		if (dup2(fds[0][0], fileno(stdin)) < 0 || dup2(fds[1][1], fileno(stdout)) < 0 )
		{
			close(fds[0][0]);
			close(fds[1][1]);

			_exit(EXIT_FAILURE);
		}

		iError = execvp(path, parameter);

		// We should never come here 
		close(fds[0][0]);
		close(fds[1][1]);

		_exit(iError);
	}
	else if (pid > (PID)0)
	{
		close(fds[0][0]);
		close(fds[1][1]);

		fd[0] = fds[1][0];
		fd[1] = fds[0][1];

		return pid;
	}
	else
	{
		close(fds[0][0]);
		close(fds[1][1]);

		close(fds[0][1]);
		close(fds[1][0]);

		return -1;
	}
#endif // OS_WIN32
}