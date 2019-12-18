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
 int PAGE_SHIFT ; 
 int PF_RANDOMIZE ; 
 TYPE_1__* current ; 
 int get_random_int () ; 
 scalar_t__ is_32bit_task () ; 

__attribute__((used)) static unsigned long mmap_rnd(void)
{
	unsigned long rnd = 0;

	if (current->flags & PF_RANDOMIZE) {
		/* 8MB for 32bit, 1GB for 64bit */
		if (is_32bit_task())
			rnd = (long)(get_random_int() % (1<<(22-PAGE_SHIFT)));
		else
			rnd = (long)(get_random_int() % (1<<(29-PAGE_SHIFT)));
	}
	return (rnd << PAGE_SHIFT) * 2;
}