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
typedef  size_t ssize_t ;

/* Variables and functions */
 int ENOTTY ; 
 int ERANGE ; 
 int /*<<< orphan*/  __procfdname (char*,int) ; 
 int errno ; 
 int /*<<< orphan*/  isatty (int) ; 
 size_t readlink (char*,char*,size_t) ; 

int ttyname_r(int fd, char *name, size_t size)
{
	char procname[sizeof "/proc/self/fd/" + 3*sizeof(int) + 2];
	ssize_t l;

	if (!isatty(fd)) return ENOTTY;

	__procfdname(procname, fd);
	l = readlink(procname, name, size);

	if (l < 0) return errno;
	else if (l == size) return ERANGE;
	else {
		name[l] = 0;
		return 0;
	}
}