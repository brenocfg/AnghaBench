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
 scalar_t__ KERN_SUCCESS ; 
 int VM_PURGABLE_NONVOLATILE ; 
 int /*<<< orphan*/  VM_PURGABLE_SET_STATE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bsd_pageable_map ; 
 scalar_t__ vm_purgable_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static kern_return_t
execargs_purgeable_reference(void *execarg_address) {
	int state = VM_PURGABLE_NONVOLATILE;
	kern_return_t kr = vm_purgable_control(bsd_pageable_map, (vm_offset_t) execarg_address, VM_PURGABLE_SET_STATE, &state);

	assert(kr == KERN_SUCCESS);
	return kr;
}