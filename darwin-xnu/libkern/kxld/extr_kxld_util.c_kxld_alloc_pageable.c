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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_KERN_MEMORY_OSKEXT ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kmem_alloc_pageable (int /*<<< orphan*/ ,scalar_t__*,size_t,int /*<<< orphan*/ ) ; 
 void* kxld_page_alloc_untracked (size_t) ; 
 size_t round_page (size_t) ; 

void *
kxld_alloc_pageable(size_t size)
{
    size = round_page(size);

#if KERNEL
    kern_return_t rval = 0;
    vm_offset_t ptr = 0;

    rval = kmem_alloc_pageable(kernel_map, &ptr, size, VM_KERN_MEMORY_OSKEXT);
    if (rval) ptr = 0;

    return (void *) ptr;
#else
    return kxld_page_alloc_untracked(size);
#endif
}