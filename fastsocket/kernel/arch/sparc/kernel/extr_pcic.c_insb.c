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
 unsigned char inb (unsigned long) ; 

void insb(unsigned long addr, void *dst, unsigned long count)
{
	while (count) {
		count -= 1;
		*(unsigned char *)dst = inb(addr);
		dst += 1;
		/* addr += 1; */
	}
}