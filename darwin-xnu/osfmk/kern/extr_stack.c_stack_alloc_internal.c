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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int KMA_GUARD_FIRST ; 
 int KMA_GUARD_LAST ; 
 int KMA_KOBJECT ; 
 int KMA_KSTACK ; 
 int KMA_ZERO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_STACK ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kernel_memory_allocate (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_stack_size ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 scalar_t__ stack_addr_mask ; 
 int /*<<< orphan*/  stack_allocs ; 
 int /*<<< orphan*/  stack_free_count ; 
 int /*<<< orphan*/  stack_free_delta ; 
 scalar_t__ stack_free_list ; 
 scalar_t__ stack_hiwat ; 
 int /*<<< orphan*/  stack_lock () ; 
 int /*<<< orphan*/  stack_new_count ; 
 scalar_t__ stack_next (scalar_t__) ; 
 scalar_t__ stack_total ; 
 int /*<<< orphan*/  stack_unlock () ; 

__attribute__((used)) static vm_offset_t
stack_alloc_internal(void)
{
	vm_offset_t		stack = 0;
	spl_t			s;
	int			flags = 0;
	kern_return_t		kr = KERN_SUCCESS;

	s = splsched();
	stack_lock();
	stack_allocs++;
	stack = stack_free_list;
	if (stack != 0) {
		stack_free_list = stack_next(stack);
		stack_free_count--;
	}
	else {
		if (++stack_total > stack_hiwat)
			stack_hiwat = stack_total;
		stack_new_count++;
	}
	stack_free_delta--;
	stack_unlock();
	splx(s);

	if (stack == 0) {

		/*
		 * Request guard pages on either side of the stack.  Ask
		 * kernel_memory_allocate() for two extra pages to account
		 * for these.
		 */

		flags = KMA_GUARD_FIRST | KMA_GUARD_LAST | KMA_KSTACK | KMA_KOBJECT | KMA_ZERO;
		kr = kernel_memory_allocate(kernel_map, &stack,
					   kernel_stack_size + (2*PAGE_SIZE),
					   stack_addr_mask,
					   flags,
					   VM_KERN_MEMORY_STACK);
		if (kr != KERN_SUCCESS) {
			panic("stack_alloc: kernel_memory_allocate(size:0x%llx, mask: 0x%llx, flags: 0x%x) failed with %d\n", (uint64_t)(kernel_stack_size + (2*PAGE_SIZE)), (uint64_t)stack_addr_mask, flags, kr);
		}

		/*
		 * The stack address that comes back is the address of the lower
		 * guard page.  Skip past it to get the actual stack base address.
		 */

		stack += PAGE_SIZE;
	}
	return stack;
}