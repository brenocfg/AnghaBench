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
struct timespec {int dummy; } ;
struct sembuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCOP_semtimedop ; 
 int /*<<< orphan*/  SYS_ipc ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ,struct sembuf*,struct timespec const*) ; 

int semtimedop(int id, struct sembuf *buf, size_t n, const struct timespec *ts)
{
#ifdef SYS_semtimedop
	return syscall(SYS_semtimedop, id, buf, n, ts);
#else
	return syscall(SYS_ipc, IPCOP_semtimedop, id, n, 0, buf, ts);
#endif
}