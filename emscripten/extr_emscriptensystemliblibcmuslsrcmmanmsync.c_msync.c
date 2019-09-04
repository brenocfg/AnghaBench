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
 int /*<<< orphan*/  SYS_msync ; 
 int syscall_cp (int /*<<< orphan*/ ,void*,size_t,int) ; 

int msync(void *start, size_t len, int flags)
{
	return syscall_cp(SYS_msync, start, len, flags);
}