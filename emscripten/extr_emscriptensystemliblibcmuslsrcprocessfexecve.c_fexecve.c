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
 scalar_t__ EBADF ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  __procfdname (char*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execve (char*,char* const*,char* const*) ; 

int fexecve(int fd, char *const argv[], char *const envp[])
{
	char buf[15 + 3*sizeof(int)];
	__procfdname(buf, fd);
	execve(buf, argv, envp);
	if (errno == ENOENT) errno = EBADF;
	return -1;
}