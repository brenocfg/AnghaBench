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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int __syscall_ret (int /*<<< orphan*/ ) ; 

int sync_file_range(int fd, off_t pos, off_t len, unsigned flags)
{
#if defined(SYS_sync_file_range2)
	return syscall(SYS_sync_file_range2, fd, flags,
		__SYSCALL_LL_E(pos), __SYSCALL_LL_E(len));
#elif defined(SYS_sync_file_range)
	return syscall(SYS_sync_file_range, fd,
		__SYSCALL_LL_O(pos), __SYSCALL_LL_E(len), flags);
#else
	return __syscall_ret(-ENOSYS);
#endif
}