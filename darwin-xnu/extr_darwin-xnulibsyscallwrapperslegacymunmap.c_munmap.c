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
 uintptr_t PAGE_MASK ; 
 int __munmap (void*,size_t) ; 
 int /*<<< orphan*/  __syscall_logger (int /*<<< orphan*/ ,uintptr_t,uintptr_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mach_task_self () ; 
 int /*<<< orphan*/  stack_logging_type_vm_deallocate ; 

int
munmap(void *addr, size_t len)
{
	size_t	offset;

	if (len == 0) {
		/*
		 * Standard compliance now requires the system to return EINVAL
		 * for munmap(addr, 0).  Return success now to maintain
		 * backwards compatibility.
		 */
		return 0;
	}
	/*
	 * Page-align "addr" since the system now requires it
	 * for standards compliance.
	 * Update "len" to reflect the adjustment and still cover the same area.
	 */
	offset = ((uintptr_t) addr) & PAGE_MASK;
	addr = (void *) (((uintptr_t) addr) & ~PAGE_MASK);
	len += offset;

	if (__syscall_logger) {
		__syscall_logger(stack_logging_type_vm_deallocate, (uintptr_t)mach_task_self(), (uintptr_t)addr, len, 0, 0);
	}

	int result = __munmap(addr, len);

	return result;
}