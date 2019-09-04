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
 int /*<<< orphan*/  IPCOP_shmget ; 
 size_t PTRDIFF_MAX ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  SYS_ipc ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 

int shmget(key_t key, size_t size, int flag)
{
	if (size > PTRDIFF_MAX) size = SIZE_MAX;
#ifdef SYS_shmget
	return syscall(SYS_shmget, key, size, flag);
#else
	return syscall(SYS_ipc, IPCOP_shmget, key, size, flag);
#endif
}