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
 int /*<<< orphan*/  ALIGN_VDSO ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned int PAGE_SHIFT ; 
 unsigned long PMD_MASK ; 
 unsigned long PMD_SIZE ; 
 int PTRS_PER_PTE ; 
 unsigned long TASK_SIZE_MAX ; 
 unsigned long align_addr (unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_random_int () ; 

__attribute__((used)) static unsigned long vdso_addr(unsigned long start, unsigned len)
{
	unsigned long addr, end;
	unsigned offset;
	end = (start + PMD_SIZE - 1) & PMD_MASK;
	if (end >= TASK_SIZE_MAX)
		end = TASK_SIZE_MAX;
	end -= len;
	/* This loses some more bits than a modulo, but is cheaper */
	offset = get_random_int() & (PTRS_PER_PTE - 1);
	addr = start + (offset << PAGE_SHIFT);
	if (addr >= end)
		addr = end;

	/*
	 * page-align it here so that get_unmapped_area doesn't
	 * align it wrongfully again to the next page. addr can come in 4K
	 * unaligned here as a result of stack start randomization.
	 */
	addr = PAGE_ALIGN(addr);
	addr = align_addr(addr, NULL, ALIGN_VDSO);

	return addr;
}