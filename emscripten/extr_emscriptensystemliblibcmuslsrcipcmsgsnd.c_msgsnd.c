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
 int /*<<< orphan*/  IPCOP_msgsnd ; 
 int /*<<< orphan*/  SYS_ipc ; 
 int syscall_cp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t,int,void const*) ; 

int msgsnd(int q, const void *m, size_t len, int flag)
{
#ifdef SYS_msgsnd
	return syscall_cp(SYS_msgsnd, q, m, len, flag);
#else
	return syscall_cp(SYS_ipc, IPCOP_msgsnd, q, len, flag, m);
#endif
}