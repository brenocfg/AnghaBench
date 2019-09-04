#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_4__ {int fd; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTDIR ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 

DIR *fdopendir(int fd)
{
	DIR *dir;
	struct stat st;

	if (fstat(fd, &st) < 0) {
		return 0;
	}
	if (!S_ISDIR(st.st_mode)) {
		errno = ENOTDIR;
		return 0;
	}
	if (!(dir = calloc(1, sizeof *dir))) {
		return 0;
	}

	fcntl(fd, F_SETFD, FD_CLOEXEC);
	dir->fd = fd;
	return dir;
}