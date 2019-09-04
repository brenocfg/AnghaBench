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
 int /*<<< orphan*/  IPCOP_msgget ; 
 int /*<<< orphan*/  SYS_ipc ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int msgget(key_t k, int flag)
{
#ifdef SYS_msgget
	return syscall(SYS_msgget, k, flag);
#else
	return syscall(SYS_ipc, IPCOP_msgget, k, flag);
#endif
}