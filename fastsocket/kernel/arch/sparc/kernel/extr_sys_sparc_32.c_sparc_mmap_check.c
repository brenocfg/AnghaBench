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
 scalar_t__ ARCH_SUN4C ; 
 int EINVAL ; 
 unsigned long PAGE_SIZE ; 
 unsigned long TASK_SIZE ; 

int sparc_mmap_check(unsigned long addr, unsigned long len)
{
	if (ARCH_SUN4C &&
	    (len > 0x20000000 ||
	     (addr < 0xe0000000 && addr + len > 0x20000000)))
		return -EINVAL;

	/* See asm-sparc/uaccess.h */
	if (len > TASK_SIZE - PAGE_SIZE || addr + len > TASK_SIZE - PAGE_SIZE)
		return -EINVAL;

	return 0;
}