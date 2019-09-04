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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int /*<<< orphan*/  SYS_fstatat ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct stat*,int /*<<< orphan*/ ) ; 

int lstat(const char *restrict path, struct stat *restrict buf)
{
#ifdef SYS_lstat
	return syscall(SYS_lstat, path, buf);
#else
	return syscall(SYS_fstatat, AT_FDCWD, path, buf, AT_SYMLINK_NOFOLLOW);
#endif
}