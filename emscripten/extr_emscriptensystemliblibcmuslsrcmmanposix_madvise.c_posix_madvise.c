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
 int MADV_DONTNEED ; 
 int /*<<< orphan*/  SYS_madvise ; 
 int __syscall (int /*<<< orphan*/ ,void*,size_t,int) ; 

int posix_madvise(void *addr, size_t len, int advice)
{
	if (advice == MADV_DONTNEED) return 0;
	return -__syscall(SYS_madvise, addr, len, advice);
}