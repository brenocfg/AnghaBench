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
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ execlp (char const*,char const*,char const*,char*) ; 
 scalar_t__ fork () ; 
 scalar_t__ pipe (int*) ; 
 scalar_t__ zpid ; 

void
ar_start_gzip(int fd, const char *gzip_prog, int wr)
{
	int fds[2];
	const char *gzip_flags;

	if (pipe(fds) < 0)
		err(1, "could not pipe");
	zpid = fork();
	if (zpid < 0)
		err(1, "could not fork");

	/* parent */
	if (zpid) {
		if (wr)
			dup2(fds[1], fd);
		else
			dup2(fds[0], fd);
		close(fds[0]);
		close(fds[1]);
	} else {
		if (wr) {
			dup2(fds[0], STDIN_FILENO);
			dup2(fd, STDOUT_FILENO);
			gzip_flags = "-c";
		} else {
			dup2(fds[1], STDOUT_FILENO);
			dup2(fd, STDIN_FILENO);
			gzip_flags = "-dc";
		}
		close(fds[0]);
		close(fds[1]);
		if (execlp(gzip_prog, gzip_prog, gzip_flags,
		    (char *)NULL) < 0)
			err(1, "could not exec");
		/* NOTREACHED */
	}
}