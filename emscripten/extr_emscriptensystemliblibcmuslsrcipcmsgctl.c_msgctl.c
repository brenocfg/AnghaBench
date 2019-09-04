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
struct msqid_ds {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCOP_msgctl ; 
 int IPC_64 ; 
 int /*<<< orphan*/  SYS_ipc ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct msqid_ds*,int /*<<< orphan*/ ) ; 

int msgctl(int q, int cmd, struct msqid_ds *buf)
{
#ifdef SYS_msgctl
	return syscall(SYS_msgctl, q, cmd | IPC_64, buf);
#else
	return syscall(SYS_ipc, IPCOP_msgctl, q, cmd | IPC_64, 0, buf, 0);
#endif
}