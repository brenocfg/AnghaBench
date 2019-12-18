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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int PAGE_SIZE ; 
 unsigned int STACK_CACHE_SIZE ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_REMOVE_KUNWIRE ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kernel_stack_size ; 
 scalar_t__ last_stack_tick ; 
 int /*<<< orphan*/  panic (char*) ; 
 unsigned int processor_count ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 scalar_t__ stack_collect_tick ; 
 unsigned int stack_free_count ; 
 scalar_t__ stack_free_delta ; 
 scalar_t__ stack_free_list ; 
 unsigned int stack_free_target ; 
 int /*<<< orphan*/  stack_lock () ; 
 scalar_t__ stack_next (scalar_t__) ; 
 int /*<<< orphan*/  stack_total ; 
 int /*<<< orphan*/  stack_unlock () ; 
 scalar_t__ vm_map_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 

void
stack_collect(void)
{
	if (stack_collect_tick != last_stack_tick) {
		unsigned int	target;
		vm_offset_t		stack;
		spl_t			s;

		s = splsched();
		stack_lock();

		target = stack_free_target + (STACK_CACHE_SIZE * processor_count);
		target += (stack_free_delta >= 0)? stack_free_delta: -stack_free_delta;

		while (stack_free_count > target) {
			stack = stack_free_list;
			stack_free_list = stack_next(stack);
			stack_free_count--; stack_total--;
			stack_unlock();
			splx(s);

			/*
			 * Get the stack base address, then decrement by one page
			 * to account for the lower guard page.  Add two extra pages
			 * to the size to account for the guard pages on both ends
			 * that were originally requested when the stack was allocated
			 * back in stack_alloc().
			 */

			stack = (vm_offset_t)vm_map_trunc_page(
				stack,
				VM_MAP_PAGE_MASK(kernel_map));
			stack -= PAGE_SIZE;
			if (vm_map_remove(
				    kernel_map,
				    stack,
				    stack + kernel_stack_size+(2*PAGE_SIZE),
				    VM_MAP_REMOVE_KUNWIRE)
			    != KERN_SUCCESS)
				panic("stack_collect: vm_map_remove");
			stack = 0;

			s = splsched();
			stack_lock();

			target = stack_free_target + (STACK_CACHE_SIZE * processor_count);
			target += (stack_free_delta >= 0)? stack_free_delta: -stack_free_delta;
		}

		last_stack_tick = stack_collect_tick;

		stack_unlock();
		splx(s);
	}
}