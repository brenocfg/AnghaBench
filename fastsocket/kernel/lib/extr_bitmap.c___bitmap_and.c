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
 int BITS_TO_LONGS (int) ; 

int __bitmap_and(unsigned long *dst, const unsigned long *bitmap1,
				const unsigned long *bitmap2, int bits)
{
	int k;
	int nr = BITS_TO_LONGS(bits);
	unsigned long result = 0;

	for (k = 0; k < nr; k++)
		result |= (dst[k] = bitmap1[k] & bitmap2[k]);
	return result != 0;
}