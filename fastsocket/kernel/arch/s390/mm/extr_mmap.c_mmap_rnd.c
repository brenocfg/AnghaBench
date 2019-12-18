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

__attribute__((used)) static unsigned long mmap_rnd(void)
{
	if (!(current->flags & PF_RANDOMIZE))
		return 0;
	/* 8MB randomization for mmap_base */
	return (get_random_int() & 0x7ffUL) << PAGE_SHIFT;
}