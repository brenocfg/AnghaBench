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
typedef  int /*<<< orphan*/  mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SUPERPAGE_SIZE ; 
 int TRUE ; 
 int VM_FLAGS_ANYWHERE ; 
 int VM_FLAGS_SUPERPAGE_SIZE_2MB ; 
 int check_kr (int,char*) ; 
 int check_nr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int mach_vm_allocate (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int mach_vm_deallocate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

boolean_t
test_deallocatesubpage() {
	int kr;
	int ret;
	mach_vm_address_t addr = 0;
	mach_vm_size_t	size = SUPERPAGE_SIZE;
	
	kr = mach_vm_allocate(mach_task_self(), &addr, size, VM_FLAGS_ANYWHERE | VM_FLAGS_SUPERPAGE_SIZE_2MB);
	if (!(ret = check_kr(kr, "mach_vm_allocate"))) return ret;
	kr = mach_vm_deallocate(mach_task_self(), addr + PAGE_SIZE, size);
	if (!(ret = check_kr(kr, "mach_vm_deallocate"))) return ret;
	if (!(ret = check_nr(addr, size, NULL))) return ret;
	return TRUE;
}