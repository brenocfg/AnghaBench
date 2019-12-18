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
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 

__attribute__((used)) static int pages_in_region(unsigned long base, long len)
{
	int count = 0;

	do {
		unsigned long new = (base + PAGE_SIZE) & PAGE_MASK;

		len -= (new - base);
		base = new;
		count++;
	} while (len > 0);

	return count;
}