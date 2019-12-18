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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  mach_vm_size_t ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;

/* Variables and functions */
 int ALLOCATION_SIZE_VM_REGION ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int VM_FLAGS_ANYWHERE ; 
 int VM_MAKE_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_TAG1 ; 
 int /*<<< orphan*/  VM_TAG2 ; 
 int getpid () ; 
 int /*<<< orphan*/  getppid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 scalar_t__ mach_vm_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pause () ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void allocate_vm_regions(void)
{
	uint64_t alloc_size = ALLOCATION_SIZE_VM_REGION, i = 0;

	printf("[%d] Allocating VM regions, each of size %lld KB\n", getpid(), (alloc_size>>10));
	for (i = 0; ; i++) {
		mach_vm_address_t addr = (mach_vm_address_t)NULL;

		/* Alternate VM tags between consecutive regions to prevent coalescing */
		int flags = VM_MAKE_TAG((i % 2)? VM_TAG1: VM_TAG2) | VM_FLAGS_ANYWHERE;

		if ((mach_vm_allocate(mach_task_self(), &addr, (mach_vm_size_t)alloc_size, flags)) != KERN_SUCCESS) {
			break;
		}
	}
	printf("[%d] Number of allocations: %lld\n", getpid(), i);

	/* Signal to the parent that we're done allocating */
	kill(getppid(), SIGUSR1);

	while (1) {
		pause();
	}
}