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
 int EINVAL ; 
 unsigned int MTRR_TYPE_WRCOMB ; 
 int PAGE_SHIFT ; 

__attribute__((used)) static int
amd_validate_add_page(unsigned long base, unsigned long size, unsigned int type)
{
	/*
	 * Apply the K6 block alignment and size rules
	 * In order
	 * o Uncached or gathering only
	 * o 128K or bigger block
	 * o Power of 2 block
	 * o base suitably aligned to the power
	 */
	if (type > MTRR_TYPE_WRCOMB || size < (1 << (17 - PAGE_SHIFT))
	    || (size & ~(size - 1)) - size || (base & (size - 1)))
		return -EINVAL;
	return 0;
}