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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ELOOP ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int O_PATH ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SYS_close ; 
 int /*<<< orphan*/  __procfdname (char*,int) ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 size_t readlink (char*,char*,int) ; 
 size_t stat (char*,struct stat*) ; 
 char* strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int sys_open (char const*,int) ; 

char *realpath(const char *restrict filename, char *restrict resolved)
{
	int fd;
	ssize_t r;
	struct stat st1, st2;
	char buf[15+3*sizeof(int)];
	char tmp[PATH_MAX];

	if (!filename) {
		errno = EINVAL;
		return 0;
	}

	fd = sys_open(filename, O_PATH|O_NONBLOCK|O_CLOEXEC);
	if (fd < 0) return 0;
	__procfdname(buf, fd);

	r = readlink(buf, tmp, sizeof tmp - 1);
	if (r < 0) goto err;
	tmp[r] = 0;

	fstat(fd, &st1);
	r = stat(tmp, &st2);
	if (r<0 || st1.st_dev != st2.st_dev || st1.st_ino != st2.st_ino) {
		if (!r) errno = ELOOP;
		goto err;
	}

	__syscall(SYS_close, fd);
	return resolved ? strcpy(resolved, tmp) : strdup(tmp);
err:
	__syscall(SYS_close, fd);
	return 0;
}