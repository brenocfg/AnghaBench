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
 int bitmap_ord_to_pos (unsigned long const*,int,int) ; 
 int bitmap_pos_to_ord (unsigned long const*,int,int) ; 
 int bitmap_weight (unsigned long const*,int) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int) ; 
 int find_first_bit (unsigned long const*,int) ; 
 int find_next_bit (unsigned long const*,int,int) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 

void bitmap_remap(unsigned long *dst, const unsigned long *src,
		const unsigned long *old, const unsigned long *new,
		int bits)
{
	int oldbit, w;

	if (dst == src)		/* following doesn't handle inplace remaps */
		return;
	bitmap_zero(dst, bits);

	w = bitmap_weight(new, bits);
	for (oldbit = find_first_bit(src, bits);
	     oldbit < bits;
	     oldbit = find_next_bit(src, bits, oldbit + 1)) {
	     	int n = bitmap_pos_to_ord(old, oldbit, bits);
		if (n < 0 || w == 0)
			set_bit(oldbit, dst);	/* identity map */
		else
			set_bit(bitmap_ord_to_pos(new, n % w, bits), dst);
	}
}