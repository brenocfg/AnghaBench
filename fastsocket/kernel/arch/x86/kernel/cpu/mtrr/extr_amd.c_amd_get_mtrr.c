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
typedef  scalar_t__ mtrr_type ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_K6_UWCCR ; 
 scalar_t__ MTRR_TYPE_UNCACHABLE ; 
 scalar_t__ MTRR_TYPE_WRCOMB ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static void
amd_get_mtrr(unsigned int reg, unsigned long *base,
	     unsigned long *size, mtrr_type *type)
{
	unsigned long low, high;

	rdmsr(MSR_K6_UWCCR, low, high);
	/* Upper dword is region 1, lower is region 0 */
	if (reg == 1)
		low = high;
	/* The base masks off on the right alignment */
	*base = (low & 0xFFFE0000) >> PAGE_SHIFT;
	*type = 0;
	if (low & 1)
		*type = MTRR_TYPE_UNCACHABLE;
	if (low & 2)
		*type = MTRR_TYPE_WRCOMB;
	if (!(low & 3)) {
		*size = 0;
		return;
	}
	/*
	 * This needs a little explaining. The size is stored as an
	 * inverted mask of bits of 128K granularity 15 bits long offset
	 * 2 bits.
	 *
	 * So to get a size we do invert the mask and add 1 to the lowest
	 * mask bit (4 as its 2 bits in). This gives us a size we then shift
	 * to turn into 128K blocks.
	 *
	 * eg              111 1111 1111 1100      is 512K
	 *
	 * invert          000 0000 0000 0011
	 * +1              000 0000 0000 0100
	 * *128K   ...
	 */
	low = (~low) & 0x1FFFC;
	*size = (low + 4) << (15 - PAGE_SHIFT);
}