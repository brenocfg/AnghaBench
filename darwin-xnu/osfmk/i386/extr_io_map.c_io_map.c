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
typedef  scalar_t__ vm_map_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_KERN_MEMORY_IOKIT ; 
 scalar_t__ VM_MAP_NULL ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  kasan_notify_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_map ; 
 int /*<<< orphan*/  kmem_alloc_pageable (scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_map (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,unsigned int) ; 
 int /*<<< orphan*/  pmap_map_bd (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,unsigned int) ; 
 scalar_t__ round_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtual_avail ; 

vm_offset_t
io_map(vm_map_offset_t phys_addr, vm_size_t size, unsigned int flags)
{
	vm_offset_t	start;

	if (kernel_map == VM_MAP_NULL) {
	    /*
	     * VM is not initialized.  Grab memory.
	     */
	    start = virtual_avail;
	    virtual_avail += round_page(size);

#if KASAN
	    kasan_notify_address(start, size);
#endif
	    (void) pmap_map_bd(start, phys_addr, phys_addr + round_page(size),
			       VM_PROT_READ|VM_PROT_WRITE,
			       flags);
	}
	else {
	    (void) kmem_alloc_pageable(kernel_map, &start, round_page(size), VM_KERN_MEMORY_IOKIT);
	    (void) pmap_map(start, phys_addr, phys_addr + round_page(size),
			    VM_PROT_READ|VM_PROT_WRITE,
			    flags);
	}
	return (start);
}