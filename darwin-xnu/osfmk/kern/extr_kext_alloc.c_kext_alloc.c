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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ mach_vm_offset_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ KERN_INVALID_ADDRESS ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int VM_FLAGS_ANYWHERE ; 
 int VM_FLAGS_FIXED ; 
 int /*<<< orphan*/  VM_INHERIT_DEFAULT ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_KEXT ; 
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int /*<<< orphan*/  VM_PROT_DEFAULT ; 
 int /*<<< orphan*/  g_kext_map ; 
 int /*<<< orphan*/  kasan_notify_address (scalar_t__,scalar_t__) ; 
 scalar_t__ kext_alloc_base ; 
 scalar_t__ kext_alloc_max ; 
 int /*<<< orphan*/  kext_free (scalar_t__,scalar_t__) ; 
 scalar_t__ kext_post_boot_base ; 
 scalar_t__ mach_vm_allocate_kernel (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mach_vm_map_kernel (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

kern_return_t
kext_alloc(vm_offset_t *_addr, vm_size_t size, boolean_t fixed)
{
    kern_return_t rval = 0;
#if CONFIG_KEXT_BASEMENT
    mach_vm_offset_t addr = (fixed) ? *_addr : kext_post_boot_base;
#else
    mach_vm_offset_t addr = (fixed) ? *_addr : kext_alloc_base;
#endif
    int flags = (fixed) ? VM_FLAGS_FIXED : VM_FLAGS_ANYWHERE;
 
#if CONFIG_KEXT_BASEMENT
    /* Allocate the kext virtual memory
     * 10608884 - use mach_vm_map since we want VM_FLAGS_ANYWHERE allocated past
     * kext_post_boot_base (when possible).  mach_vm_allocate will always 
     * start at 0 into the map no matter what you pass in addr.  We want non 
     * fixed (post boot) kext allocations to start looking for free space 
     * just past where prelinked kexts have loaded.  
     */
    rval = mach_vm_map_kernel(g_kext_map,
                       &addr, 
                       size, 
                       0,
                       flags,
		       VM_MAP_KERNEL_FLAGS_NONE,
                       VM_KERN_MEMORY_KEXT,
                       MACH_PORT_NULL,
                       0,
                       TRUE,
                       VM_PROT_DEFAULT,
                       VM_PROT_ALL,
                       VM_INHERIT_DEFAULT);
    if (rval != KERN_SUCCESS) {
        printf("mach_vm_map failed - %d\n", rval);
        goto finish;
    }
#else
    rval = mach_vm_allocate_kernel(g_kext_map, &addr, size, flags, VM_KERN_MEMORY_KEXT);
    if (rval != KERN_SUCCESS) {
        printf("vm_allocate failed - %d\n", rval);
        goto finish;
    }
#endif

    /* Check that the memory is reachable by kernel text */
    if ((addr + size) > kext_alloc_max) {
        kext_free((vm_offset_t)addr, size);
        rval = KERN_INVALID_ADDRESS;
        goto finish;
    }

    *_addr = (vm_offset_t)addr;
    rval = KERN_SUCCESS;
#if KASAN
    kasan_notify_address(addr, size);
#endif

finish:
    return rval;
}