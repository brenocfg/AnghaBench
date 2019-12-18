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
 unsigned short inw (unsigned long) ; 

void insw(unsigned long addr, void *dst, unsigned long count)
{
	while (count) {
		count -= 2;
		*(unsigned short *)dst = inw(addr);
		dst += 2;
		/* addr += 2; */
	}
}