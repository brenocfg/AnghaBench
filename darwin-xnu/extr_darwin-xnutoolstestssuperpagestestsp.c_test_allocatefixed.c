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
typedef  int /*<<< orphan*/  mach_vm_address_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_ADDRESS1 ; 
 int /*<<< orphan*/  SUPERPAGE_SIZE ; 
 int TRUE ; 
 int /*<<< orphan*/  VM_FLAGS_SUPERPAGE_SIZE_2MB ; 
 int check_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int check_kr (int,char*) ; 
 int check_nr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int check_rw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int mach_vm_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mach_vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
test_allocatefixed() {
	int kr;
	int ret;
	mach_vm_address_t addr = FIXED_ADDRESS1;
	mach_vm_size_t	size = SUPERPAGE_SIZE;

	kr = mach_vm_allocate(mach_task_self(), &addr, size, VM_FLAGS_SUPERPAGE_SIZE_2MB);
	if (!(ret = check_kr(kr, "mach_vm_allocate"))) return ret;
	if (!(ret = check_addr(addr, FIXED_ADDRESS1, "mach_vm_allocate"))) return ret;
	if (!(ret = check_rw(addr, size))) return ret;
	kr = mach_vm_deallocate(mach_task_self(), addr, size);
	if (!(ret = check_kr(kr, "mach_vm_deallocate"))) return ret;
	if (!(ret = check_nr(addr, size, NULL))) return ret;
	return TRUE;
}