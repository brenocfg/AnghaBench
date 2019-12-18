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
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  __set_phys_to_machine (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  alloc_p2m (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void set_phys_to_machine(unsigned long pfn, unsigned long mfn)
{
	if (unlikely(!__set_phys_to_machine(pfn, mfn)))  {
		alloc_p2m(pfn);

		if (!__set_phys_to_machine(pfn, mfn))
			BUG();
	}
}