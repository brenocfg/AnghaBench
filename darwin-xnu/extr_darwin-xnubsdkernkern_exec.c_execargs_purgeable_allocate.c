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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSD_PAGEABLE_SIZE_PER_EXEC ; 
 scalar_t__ KERN_SUCCESS ; 
 int VM_FLAGS_ANYWHERE ; 
 int VM_FLAGS_PURGABLE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bsd_pageable_map ; 
 scalar_t__ vm_allocate_kernel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
execargs_purgeable_allocate(char **execarg_address) {
	kern_return_t kr = vm_allocate_kernel(bsd_pageable_map, (vm_offset_t *)execarg_address, BSD_PAGEABLE_SIZE_PER_EXEC, VM_FLAGS_ANYWHERE | VM_FLAGS_PURGABLE, VM_KERN_MEMORY_NONE);
	assert(kr == KERN_SUCCESS);
	return kr;
}