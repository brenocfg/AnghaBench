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
typedef  int uint8_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ _COMM_PAGE_KERNEL_PAGE_SHIFT ; 
 scalar_t__ _COMM_PAGE_USER_PAGE_SHIFT_32 ; 
 scalar_t__ _COMM_PAGE_USER_PAGE_SHIFT_64 ; 
 int /*<<< orphan*/  _init_cpu_capabilities () ; 
 int /*<<< orphan*/  _pthread_set_self (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _task_reply_port ; 
 int /*<<< orphan*/  mach_reply_port () ; 
 int /*<<< orphan*/  mach_task_self_ ; 
 int /*<<< orphan*/  task_self_trap () ; 
 int vm_kernel_page_mask ; 
 int vm_kernel_page_shift ; 
 int vm_kernel_page_size ; 
 int vm_page_mask ; 
 int vm_page_shift ; 
 int vm_page_size ; 

void
mach_init_doit(void)
{
	// Initialize cached mach ports defined in mach_init.h
	mach_task_self_ = task_self_trap();
	_task_reply_port = mach_reply_port();

	if (vm_kernel_page_shift == 0) {
#ifdef	_COMM_PAGE_KERNEL_PAGE_SHIFT
		vm_kernel_page_shift = *(uint8_t*) _COMM_PAGE_KERNEL_PAGE_SHIFT;
		vm_kernel_page_size = 1 << vm_kernel_page_shift;
		vm_kernel_page_mask = vm_kernel_page_size - 1;
#else
		vm_kernel_page_size = PAGE_SIZE;
		vm_kernel_page_mask = PAGE_MASK;
		vm_kernel_page_shift = PAGE_SHIFT;
#endif /* _COMM_PAGE_KERNEL_PAGE_SHIFT */
	}
	
	if (vm_page_shift == 0) {
#if defined(__arm64__)
		vm_page_shift = *(uint8_t*) _COMM_PAGE_USER_PAGE_SHIFT_64;
#elif defined(__arm__)
		vm_page_shift = *(uint8_t*) _COMM_PAGE_USER_PAGE_SHIFT_32;
#else
		vm_page_shift = vm_kernel_page_shift;
#endif
		vm_page_size = 1 << vm_page_shift;
		vm_page_mask = vm_page_size - 1;
	}

	_init_cpu_capabilities();
	_pthread_set_self(0);
}