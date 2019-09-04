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
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_REMOVEDIR ; 
 int EISDIR ; 
 int /*<<< orphan*/  SYS_unlinkat ; 
 int __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int __syscall_ret (int) ; 

int remove(const char *path)
{
#ifdef SYS_unlink
	int r = __syscall(SYS_unlink, path);
#else
	int r = __syscall(SYS_unlinkat, AT_FDCWD, path, 0);
#endif
#ifdef SYS_rmdir
	if (r==-EISDIR) r = __syscall(SYS_rmdir, path);
#else
	if (r==-EISDIR) r = __syscall(SYS_unlinkat, AT_FDCWD, path, AT_REMOVEDIR);
#endif
	return __syscall_ret(r);
}