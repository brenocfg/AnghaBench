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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  g_kext_map ; 
 scalar_t__ mach_vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
kext_free(vm_offset_t addr, vm_size_t size)
{
    kern_return_t rval;

    rval = mach_vm_deallocate(g_kext_map, addr, size);
    assert(rval == KERN_SUCCESS);
}