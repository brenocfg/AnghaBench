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
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SUPERPAGE_SIZE ; 
 int TRUE ; 
 int VM_FLAGS_ANYWHERE ; 
 int VM_FLAGS_SUPERPAGE_SIZE_2MB ; 
 int check_addr0 (scalar_t__,char*) ; 
 int check_align (scalar_t__) ; 
 int check_kr (int,char*) ; 
 int check_rw (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ global_addr ; 
 int /*<<< orphan*/  global_size ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int mach_vm_allocate (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int) ; 

boolean_t
test_allocate() {
	int kr, ret;

	global_addr = 0;
	global_size = SUPERPAGE_SIZE;
	
	kr = mach_vm_allocate(mach_task_self(), &global_addr, global_size, VM_FLAGS_ANYWHERE | VM_FLAGS_SUPERPAGE_SIZE_2MB);
	if (!(ret = check_kr(kr, "mach_vm_allocate"))) return ret;
	if (!(ret = check_addr0(global_addr, "mach_vm_allocate"))) return ret;
	if (!(ret = check_align(global_addr))) return ret;
	if (!(ret = check_rw(global_addr, global_size))) return ret;

	return TRUE;
}