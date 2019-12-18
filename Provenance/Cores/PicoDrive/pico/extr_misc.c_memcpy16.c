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
 int /*<<< orphan*/  memcpy32 (int*,int*,int) ; 

void memcpy16(unsigned short *dest, unsigned short *src, int count)
{
	if ((((long)dest | (long)src) & 3) == 0)
	{
		if (count >= 32) {
			memcpy32((int *)dest, (int *)src, count/2);
			count&=1;
		} else {
			for (; count >= 2; count -= 2, dest+=2, src+=2)
				*(int *)dest = *(int *)src;
		}
	}
	while (count--)
		*dest++ = *src++;
}