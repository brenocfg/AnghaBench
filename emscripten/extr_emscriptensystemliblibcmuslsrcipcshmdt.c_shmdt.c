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
 int /*<<< orphan*/  IPCOP_shmdt ; 
 int /*<<< orphan*/  SYS_ipc ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 

int shmdt(const void *addr)
{
#ifdef SYS_shmdt
	return syscall(SYS_shmdt, addr);
#else
	return syscall(SYS_ipc, IPCOP_shmdt, 0, 0, 0, addr);
#endif
}