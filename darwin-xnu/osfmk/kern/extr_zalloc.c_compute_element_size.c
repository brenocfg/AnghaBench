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
typedef  int vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */

__attribute__((used)) static vm_size_t
compute_element_size(vm_size_t requested_size)
{
	vm_size_t element_size = requested_size;

	/* Zone elements must fit both a next pointer and a backup pointer */
	vm_size_t  minimum_element_size = sizeof(vm_offset_t) * 2;
	if (element_size < minimum_element_size)
		element_size = minimum_element_size;

	/*
	 *  Round element size to a multiple of sizeof(pointer)
	 *  This also enforces that allocations will be aligned on pointer boundaries
	 */
	element_size = ((element_size-1) + sizeof(vm_offset_t)) -
	       ((element_size-1) % sizeof(vm_offset_t));

	return element_size;
}