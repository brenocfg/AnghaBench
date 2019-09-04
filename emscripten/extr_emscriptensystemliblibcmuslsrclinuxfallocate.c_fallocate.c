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
 int /*<<< orphan*/  SYS_fallocate ; 
 int /*<<< orphan*/  __SYSCALL_LL_E (int /*<<< orphan*/ ) ; 
 int syscall (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fallocate(int fd, int mode, off_t base, off_t len)
{
	return syscall(SYS_fallocate, fd, mode, __SYSCALL_LL_E(base),
		__SYSCALL_LL_E(len));
}