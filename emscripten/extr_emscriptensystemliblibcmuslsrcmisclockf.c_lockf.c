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
struct flock {int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_pid; int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_whence; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  F_GETLK ; 
#define  F_LOCK 131 
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_SETLKW ; 
#define  F_TEST 130 
#define  F_TLOCK 129 
#define  F_ULOCK 128 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  getpid () ; 

int lockf(int fd, int op, off_t size)
{
	struct flock l = {
		.l_type = F_WRLCK,
		.l_whence = SEEK_CUR,
		.l_len = size,
	};
	switch (op) {
	case F_TEST:
		l.l_type = F_RDLCK;
		if (fcntl(fd, F_GETLK, &l) < 0)
			return -1;
		if (l.l_type == F_UNLCK || l.l_pid == getpid())
			return 0;
		errno = EACCES;
		return -1;
	case F_ULOCK:
		l.l_type = F_UNLCK;
	case F_TLOCK:
		return fcntl(fd, F_SETLK, &l);
	case F_LOCK:
		return fcntl(fd, F_SETLKW, &l);
	}
	errno = EINVAL;
	return -1;
}