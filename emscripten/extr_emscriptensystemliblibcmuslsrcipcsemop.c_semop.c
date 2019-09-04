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
struct sembuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCOP_semop ; 
 int /*<<< orphan*/  SYS_ipc ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ,struct sembuf*) ; 

int semop(int id, struct sembuf *buf, size_t n)
{
#ifdef SYS_semop
	return syscall(SYS_semop, id, buf, n);
#else
	return syscall(SYS_ipc, IPCOP_semop, id, n, 0, buf);
#endif
}