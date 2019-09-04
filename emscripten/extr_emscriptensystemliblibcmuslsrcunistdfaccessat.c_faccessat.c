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
struct ctx {int fd; char const* filename; int amode; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int AT_EACCESS ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SYS_faccessat ; 
 int /*<<< orphan*/  SYS_wait4 ; 
 size_t WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSIGNALED (int) ; 
 int /*<<< orphan*/  __WCLONE ; 
 int /*<<< orphan*/  __block_all_sigs (int /*<<< orphan*/ *) ; 
 scalar_t__ __clone (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct ctx*) ; 
 int /*<<< orphan*/  __restore_sigs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,scalar_t__,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __syscall_ret (int) ; 
 int /*<<< orphan*/  checker ; 
 int* errors ; 
 scalar_t__ getegid () ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getgid () ; 
 scalar_t__ getuid () ; 
 int syscall (int /*<<< orphan*/ ,int,char const*,int,int) ; 

int faccessat(int fd, const char *filename, int amode, int flag)
{
	if (!flag || (flag==AT_EACCESS && getuid()==geteuid() && getgid()==getegid()))
		return syscall(SYS_faccessat, fd, filename, amode, flag);

	if (flag != AT_EACCESS)
		return __syscall_ret(-EINVAL);

	char stack[1024];
	sigset_t set;
	pid_t pid;
	int ret = -EBUSY;
	struct ctx c = { .fd = fd, .filename = filename, .amode = amode };

	__block_all_sigs(&set);
	
	pid = __clone(checker, stack+sizeof stack, 0, &c);
	if (pid > 0) {
		int status;
		do {
			__syscall(SYS_wait4, pid, &status, __WCLONE, 0);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		if (WIFEXITED(status))
			ret = errors[WEXITSTATUS(status)];
	}

	__restore_sigs(&set);

	return __syscall_ret(ret);
}