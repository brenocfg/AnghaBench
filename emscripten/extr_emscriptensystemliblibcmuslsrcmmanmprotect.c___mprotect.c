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
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  SYS_mprotect ; 
 int syscall (int /*<<< orphan*/ ,size_t,size_t,int) ; 

int __mprotect(void *addr, size_t len, int prot)
{
	size_t start, end;
	start = (size_t)addr & -PAGE_SIZE;
	end = (size_t)((char *)addr + len + PAGE_SIZE-1) & -PAGE_SIZE;
	return syscall(SYS_mprotect, start, end-start, prot);
}