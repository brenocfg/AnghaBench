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
typedef  int /*<<< orphan*/  mach_vm_address_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int TRUE ; 
 int VM_FLAGS_ANYWHERE ; 
 int VM_FLAGS_SUPERPAGE_SIZE_ANY ; 
 int check_addr0 (int /*<<< orphan*/ ,char*) ; 
 int check_kr (int,char*) ; 
 int check_nr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int check_rw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int mach_vm_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int mach_vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

boolean_t
test_allocate_size_any() {
	int kr;
	int ret;
	mach_vm_address_t addr = 0;
	mach_vm_size_t	size = 2*PAGE_SIZE; /* will be rounded up to some superpage size */

	kr = mach_vm_allocate(mach_task_self(), &addr, size, VM_FLAGS_ANYWHERE | VM_FLAGS_SUPERPAGE_SIZE_ANY);
	if (!(ret = check_kr(kr, "mach_vm_allocate"))) return ret;
	if (!(ret = check_addr0(addr, "mach_vm_allocate"))) return ret;
	if (!(ret = check_rw(addr, size))) return ret;
	kr = mach_vm_deallocate(mach_task_self(), addr, size);
	if (!(ret = check_kr(kr, "mach_vm_deallocate"))) return ret;
	if (!(ret = check_nr(addr, size, NULL))) return ret;
	return TRUE;
}