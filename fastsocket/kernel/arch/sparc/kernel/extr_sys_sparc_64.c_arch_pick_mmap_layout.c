#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int /*<<< orphan*/  unmap_area; int /*<<< orphan*/  get_unmapped_area; scalar_t__ mmap_base; } ;
struct TYPE_6__ {int flags; int personality; TYPE_2__* signal; } ;
struct TYPE_5__ {TYPE_1__* rlim; } ;
struct TYPE_4__ {unsigned long rlim_cur; } ;

/* Variables and functions */
 int ADDR_COMPAT_LAYOUT ; 
 scalar_t__ PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 int PF_RANDOMIZE ; 
 size_t RLIMIT_STACK ; 
 unsigned long RLIM_INFINITY ; 
 unsigned long STACK_TOP32 ; 
 scalar_t__ TASK_UNMAPPED_BASE ; 
 int /*<<< orphan*/  TIF_32BIT ; 
 int /*<<< orphan*/  arch_get_unmapped_area ; 
 int /*<<< orphan*/  arch_get_unmapped_area_topdown ; 
 int /*<<< orphan*/  arch_unmap_area ; 
 int /*<<< orphan*/  arch_unmap_area_topdown ; 
 TYPE_3__* current ; 
 unsigned long get_random_int () ; 
 scalar_t__ sysctl_legacy_va_layout ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

void arch_pick_mmap_layout(struct mm_struct *mm)
{
	unsigned long random_factor = 0UL;

	if (current->flags & PF_RANDOMIZE) {
		random_factor = get_random_int();
		if (test_thread_flag(TIF_32BIT))
			random_factor &= ((1 * 1024 * 1024) - 1);
		else
			random_factor = ((random_factor << PAGE_SHIFT) &
					 0xffffffffUL);
	}

	/*
	 * Fall back to the standard layout if the personality
	 * bit is set, or if the expected stack growth is unlimited:
	 */
	if (!test_thread_flag(TIF_32BIT) ||
	    (current->personality & ADDR_COMPAT_LAYOUT) ||
	    current->signal->rlim[RLIMIT_STACK].rlim_cur == RLIM_INFINITY ||
	    sysctl_legacy_va_layout) {
		mm->mmap_base = TASK_UNMAPPED_BASE + random_factor;
		mm->get_unmapped_area = arch_get_unmapped_area;
		mm->unmap_area = arch_unmap_area;
	} else {
		/* We know it's 32-bit */
		unsigned long task_size = STACK_TOP32;
		unsigned long gap;

		gap = current->signal->rlim[RLIMIT_STACK].rlim_cur;
		if (gap < 128 * 1024 * 1024)
			gap = 128 * 1024 * 1024;
		if (gap > (task_size / 6 * 5))
			gap = (task_size / 6 * 5);

		mm->mmap_base = PAGE_ALIGN(task_size - gap - random_factor);
		mm->get_unmapped_area = arch_get_unmapped_area_topdown;
		mm->unmap_area = arch_unmap_area_topdown;
	}
}