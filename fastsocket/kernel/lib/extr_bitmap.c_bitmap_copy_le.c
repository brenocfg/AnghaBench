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
 int BITS_PER_LONG ; 
 unsigned long cpu_to_le32 (unsigned long const) ; 
 unsigned long cpu_to_le64 (unsigned long const) ; 

void bitmap_copy_le(void *dst, const unsigned long *src, int nbits)
{
	unsigned long *d = dst;
	int i;

	for (i = 0; i < nbits/BITS_PER_LONG; i++) {
		if (BITS_PER_LONG == 64)
			d[i] = cpu_to_le64(src[i]);
		else
			d[i] = cpu_to_le32(src[i]);
	}
}