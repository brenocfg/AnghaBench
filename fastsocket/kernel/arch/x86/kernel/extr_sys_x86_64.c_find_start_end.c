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
 unsigned long MAP_32BIT ; 
 int PF_RANDOMIZE ; 
 unsigned long TASK_SIZE ; 
 unsigned long TASK_UNMAPPED_BASE ; 
 int /*<<< orphan*/  TIF_IA32 ; 
 TYPE_1__* current ; 
 unsigned long randomize_range (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_start_end(unsigned long flags, unsigned long *begin,
			   unsigned long *end)
{
	if (!test_thread_flag(TIF_IA32) && (flags & MAP_32BIT)) {
		unsigned long new_begin;
		/* This is usually used needed to map code in small
		   model, so it needs to be in the first 31bit. Limit
		   it to that.  This means we need to move the
		   unmapped base down for this case. This can give
		   conflicts with the heap, but we assume that glibc
		   malloc knows how to fall back to mmap. Give it 1GB
		   of playground for now. -AK */
		*begin = 0x40000000;
		*end = 0x80000000;
		if (current->flags & PF_RANDOMIZE) {
			new_begin = randomize_range(*begin, *begin + 0x02000000, 0);
			if (new_begin)
				*begin = new_begin;
		}
	} else {
		*begin = TASK_UNMAPPED_BASE;
		*end = TASK_SIZE;
	}
}