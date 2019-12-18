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

void bitmap_fold(unsigned long *dst, const unsigned long *orig,
			int sz, int bits)
{
	int oldbit;

	if (dst == orig)	/* following doesn't handle inplace mappings */
		return;
	bitmap_zero(dst, bits);

	for (oldbit = find_first_bit(orig, bits);
	     oldbit < bits;
	     oldbit = find_next_bit(orig, bits, oldbit + 1))
		set_bit(oldbit % sz, dst);
}