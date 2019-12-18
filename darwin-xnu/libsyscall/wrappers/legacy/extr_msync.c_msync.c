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
 uintptr_t PAGE_MASK ; 
 int __msync_nocancel (void*,size_t,int) ; 

int
msync(void *addr, size_t len, int flags)
{
	size_t	offset;

	/*
	 * Page-align "addr" since the system now requires it
	 * for standards compliance.
	 * Update "len" to reflect the alignment.
	 */
	offset = ((uintptr_t) addr) & PAGE_MASK;
	addr = (void *) (((uintptr_t) addr) & ~PAGE_MASK);
	len += offset;
	return __msync_nocancel(addr, len, flags);
}