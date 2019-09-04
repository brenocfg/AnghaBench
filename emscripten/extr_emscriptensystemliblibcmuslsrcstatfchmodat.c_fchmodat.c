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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int AT_SYMLINK_NOFOLLOW ; 
 int EINVAL ; 
 int ELOOP ; 
 int EOPNOTSUPP ; 
 int O_CLOEXEC ; 
 int O_NOCTTY ; 
 int O_NOFOLLOW ; 
 int O_PATH ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SYS_close ; 
 int /*<<< orphan*/  SYS_fchmodat ; 
 int /*<<< orphan*/  SYS_fstatat ; 
 int /*<<< orphan*/  SYS_openat ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __procfdname (char*,int) ; 
 int __syscall (int /*<<< orphan*/ ,int,...) ; 
 int __syscall_ret (int) ; 
 int syscall (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int) ; 

int fchmodat(int fd, const char *path, mode_t mode, int flag)
{
	if (!flag) return syscall(SYS_fchmodat, fd, path, mode, flag);

	if (flag != AT_SYMLINK_NOFOLLOW)
		return __syscall_ret(-EINVAL);

	struct stat st;
	int ret, fd2;
	char proc[15+3*sizeof(int)];

	if ((ret = __syscall(SYS_fstatat, fd, path, &st, flag)))
		return __syscall_ret(ret);
	if (S_ISLNK(st.st_mode))
		return __syscall_ret(-EOPNOTSUPP);

	if ((fd2 = __syscall(SYS_openat, fd, path, O_RDONLY|O_PATH|O_NOFOLLOW|O_NOCTTY|O_CLOEXEC)) < 0) {
		if (fd2 == -ELOOP)
			return __syscall_ret(-EOPNOTSUPP);
		return __syscall_ret(fd2);
	}

	__procfdname(proc, fd2);
	ret = __syscall(SYS_fstatat, AT_FDCWD, proc, &st, 0);
	if (!ret) {
		if (S_ISLNK(st.st_mode)) ret = -EOPNOTSUPP;
		else ret = __syscall(SYS_fchmodat, AT_FDCWD, proc, mode);
	}

	__syscall(SYS_close, fd2);
	return __syscall_ret(ret);
}