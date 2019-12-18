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
typedef  int mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int PAGE_SIZE ; 
 int SUPERPAGE_SIZE ; 
 int TRUE ; 
 int VM_FLAGS_ANYWHERE ; 
 int VM_FLAGS_SUPERPAGE_SIZE_2MB ; 
 int check_kr (int,char*) ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int mach_vm_allocate (int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 int mach_vm_deallocate (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

boolean_t
test_reallocate() {
	mach_vm_address_t addr = 0, addr2;
	mach_vm_size_t	size = SUPERPAGE_SIZE;
	int kr, ret;
	int i;

	kr = mach_vm_allocate(mach_task_self(), &addr, size, VM_FLAGS_ANYWHERE | VM_FLAGS_SUPERPAGE_SIZE_2MB);
	if (!(ret = check_kr(kr, "mach_vm_allocate"))) return ret;

	/* attempt to allocate every sub-page of superpage */
	for (i=0; i<SUPERPAGE_SIZE/PAGE_SIZE; i++) {
		addr2 = addr + i*PAGE_SIZE;
		size = PAGE_SIZE;
		kr = mach_vm_allocate(mach_task_self(), &addr2, size, 0);
		if ((ret = check_kr(kr, "mach_vm_allocate"))) {
			sprintf(error, "could allocate already allocated space, page %d", i);
			mach_vm_deallocate(mach_task_self(), addr, size);
			return FALSE;
		}
	}
	kr = mach_vm_deallocate(mach_task_self(), addr, size);
	if (!(ret = check_kr(kr, "mach_vm_deallocate"))) return ret;
	return TRUE;
}