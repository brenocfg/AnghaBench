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
typedef  int /*<<< orphan*/  key_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IPCOP_semget ; 
 int /*<<< orphan*/  SYS_ipc ; 
 int USHRT_MAX ; 
 int __syscall_ret (int /*<<< orphan*/ ) ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int semget(key_t key, int n, int fl)
{
	/* The kernel uses the wrong type for the sem_nsems member
	 * of struct semid_ds, and thus might not check that the
	 * n fits in the correct (per POSIX) userspace type, so
	 * we have to check here. */
	if (n > USHRT_MAX) return __syscall_ret(-EINVAL);
#ifdef SYS_semget
	return syscall(SYS_semget, key, n, fl);
#else
	return syscall(SYS_ipc, IPCOP_semget, key, n, fl);
#endif
}