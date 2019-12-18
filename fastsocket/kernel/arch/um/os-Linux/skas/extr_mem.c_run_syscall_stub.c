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
struct mm_id {int dummy; } ;

/* Variables and functions */
 unsigned long UM_KERN_PAGE_MASK ; 
 int UM_KERN_PAGE_SIZE ; 
 unsigned long* check_init_stack (struct mm_id*,void*) ; 
 long do_syscall_stub (struct mm_id*,void**) ; 
 int /*<<< orphan*/  multi_op_count ; 
 int /*<<< orphan*/  single_count ; 

long run_syscall_stub(struct mm_id * mm_idp, int syscall,
		      unsigned long *args, long expected, void **addr,
		      int done)
{
	unsigned long *stack = check_init_stack(mm_idp, *addr);

	if (done && *addr == NULL)
		single_count++;

	*stack += sizeof(long);
	stack += *stack / sizeof(long);

	*stack++ = syscall;
	*stack++ = args[0];
	*stack++ = args[1];
	*stack++ = args[2];
	*stack++ = args[3];
	*stack++ = args[4];
	*stack++ = args[5];
	*stack++ = expected;
	*stack = 0;
	multi_op_count++;

	if (!done && ((((unsigned long) stack) & ~UM_KERN_PAGE_MASK) <
		     UM_KERN_PAGE_SIZE - 10 * sizeof(long))) {
		*addr = stack;
		return 0;
	}

	return do_syscall_stub(mm_idp, addr);
}