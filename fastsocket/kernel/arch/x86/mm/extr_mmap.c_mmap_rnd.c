#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int PF_RANDOMIZE ; 
 TYPE_1__* current ; 
 int get_random_int () ; 
 scalar_t__ mmap_is_ia32 () ; 

__attribute__((used)) static unsigned long mmap_rnd(void)
{
	unsigned long rnd = 0;

	/*
	*  8 bits of randomness in 32bit mmaps, 20 address space bits
	* 28 bits of randomness in 64bit mmaps, 40 address space bits
	*/
	if (current->flags & PF_RANDOMIZE) {
		if (mmap_is_ia32())
			rnd = get_random_int() % (1<<8);
		else
			rnd = get_random_int() % (1<<28);
	}
	return rnd << PAGE_SHIFT;
}