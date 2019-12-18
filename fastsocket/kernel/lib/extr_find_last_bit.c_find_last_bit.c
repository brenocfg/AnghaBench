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
 unsigned long BITS_PER_LONG ; 
 unsigned long __fls (unsigned long) ; 

unsigned long find_last_bit(const unsigned long *addr, unsigned long size)
{
	unsigned long words;
	unsigned long tmp;

	/* Start at final word. */
	words = size / BITS_PER_LONG;

	/* Partial final word? */
	if (size & (BITS_PER_LONG-1)) {
		tmp = (addr[words] & (~0UL >> (BITS_PER_LONG
					 - (size & (BITS_PER_LONG-1)))));
		if (tmp)
			goto found;
	}

	while (words) {
		tmp = addr[--words];
		if (tmp) {
found:
			return words * BITS_PER_LONG + __fls(tmp);
		}
	}

	/* Not found */
	return size;
}