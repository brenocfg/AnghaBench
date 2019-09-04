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
 int /*<<< orphan*/  SYS_fadvise ; 
 int /*<<< orphan*/  __SYSCALL_LL_E (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __SYSCALL_LL_O (int /*<<< orphan*/ ) ; 
 int __syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int posix_fadvise(int fd, off_t base, off_t len, int advice)
{
#if defined(SYSCALL_FADVISE_6_ARG)
	/* Some archs, at least arm and powerpc, have the syscall
	 * arguments reordered to avoid needing 7 argument registers
	 * due to 64-bit argument alignment. */
	return -__syscall(SYS_fadvise, fd, advice,
		__SYSCALL_LL_E(base), __SYSCALL_LL_E(len));
#else
	return -__syscall(SYS_fadvise, fd, __SYSCALL_LL_O(base),
		__SYSCALL_LL_E(len), advice);
#endif
}