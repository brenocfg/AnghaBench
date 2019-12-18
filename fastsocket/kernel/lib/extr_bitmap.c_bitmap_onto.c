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
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int) ; 
 int find_first_bit (unsigned long const*,int) ; 
 int find_next_bit (unsigned long const*,int,int) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 scalar_t__ test_bit (int,unsigned long const*) ; 

void bitmap_onto(unsigned long *dst, const unsigned long *orig,
			const unsigned long *relmap, int bits)
{
	int n, m;       	/* same meaning as in above comment */

	if (dst == orig)	/* following doesn't handle inplace mappings */
		return;
	bitmap_zero(dst, bits);

	/*
	 * The following code is a more efficient, but less
	 * obvious, equivalent to the loop:
	 *	for (m = 0; m < bitmap_weight(relmap, bits); m++) {
	 *		n = bitmap_ord_to_pos(orig, m, bits);
	 *		if (test_bit(m, orig))
	 *			set_bit(n, dst);
	 *	}
	 */

	m = 0;
	for (n = find_first_bit(relmap, bits);
	     n < bits;
	     n = find_next_bit(relmap, bits, n + 1)) {
		/* m == bitmap_pos_to_ord(relmap, n, bits) */
		if (test_bit(m, orig))
			set_bit(n, dst);
		m++;
	}
}