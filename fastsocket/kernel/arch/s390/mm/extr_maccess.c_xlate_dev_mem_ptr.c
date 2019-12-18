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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 scalar_t__ get_swapped (unsigned long) ; 
 scalar_t__ is_swapped (unsigned long) ; 
 int /*<<< orphan*/  memcpy_real (void*,void*,unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  put_online_cpus () ; 

void *xlate_dev_mem_ptr(unsigned long addr)
{
	void *bounce = (void *) addr;
	unsigned long size;

	get_online_cpus();
	preempt_disable();
	if (is_swapped(addr)) {
		size = PAGE_SIZE - (addr & ~PAGE_MASK);
		bounce = (void *) __get_free_page(GFP_ATOMIC);
		if (bounce)
			memcpy_real(bounce, (void *) get_swapped(addr), size);
	}
	preempt_enable();
	put_online_cpus();
	return bounce;
}