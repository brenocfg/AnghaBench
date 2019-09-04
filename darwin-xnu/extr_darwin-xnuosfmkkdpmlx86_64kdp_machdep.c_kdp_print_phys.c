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
 scalar_t__ DADDR2 ; 
 scalar_t__ DMAP2 ; 
 int /*<<< orphan*/  invlpg (uintptr_t) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 

void
kdp_print_phys(int src)
{
	unsigned int   *iptr;
	int             i;

	*(int *) DMAP2 = 0x63 | (src & 0xfffff000);
	invlpg((uintptr_t) DADDR2);
	iptr = (unsigned int *) DADDR2;
	for (i = 0; i < 100; i++) {
		kprintf("0x%x ", *iptr++);
		if ((i % 8) == 0)
			kprintf("\n");
	}
	kprintf("\n");
	*(int *) DMAP2 = 0;

}