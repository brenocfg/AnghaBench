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
typedef  unsigned long long mach_vm_address_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  VM_FLAGS_FIXED ; 
 int /*<<< orphan*/  current_task () ; 
 scalar_t__ mach_vm_allocate (int /*<<< orphan*/ ,unsigned long long*,int,int /*<<< orphan*/ ) ; 

int main(void)
{
	kern_return_t kr;
	mach_vm_address_t addr = 50ULL * 1024ULL * 1024ULL * 1024ULL;

	kr = mach_vm_allocate(current_task(), &addr, 4096, VM_FLAGS_FIXED);

	if (kr == KERN_SUCCESS) {
		return 0;
	} else {
		return 1;
	}
}