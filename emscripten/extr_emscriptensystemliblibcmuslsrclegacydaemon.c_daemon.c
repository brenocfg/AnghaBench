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
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ dup2 (int,int) ; 
 int fork () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ setsid () ; 

int daemon(int nochdir, int noclose)
{
	if (!nochdir && chdir("/"))
		return -1;
	if (!noclose) {
		int fd, failed = 0;
		if ((fd = open("/dev/null", O_RDWR)) < 0) return -1;
		if (dup2(fd, 0) < 0 || dup2(fd, 1) < 0 || dup2(fd, 2) < 0)
			failed++;
		if (fd > 2) close(fd);
		if (failed) return -1;
	}

	switch(fork()) {
	case 0: break;
	case -1: return -1;
	default: _exit(0);
	}

	if (setsid() < 0) return -1;

	switch(fork()) {
	case 0: break;
	case -1: return -1;
	default: _exit(0);
	}

	return 0;
}