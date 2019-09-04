#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_1__* vm_map_copy_t ;
typedef  scalar_t__ vm_map_address_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_9__ {int /*<<< orphan*/  entries_pageable; } ;
struct TYPE_8__ {TYPE_2__ cpy_hdr; scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_INVALID_ADDRESS ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  PAGE_MASK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_INHERIT_SHARE ; 
 int /*<<< orphan*/  VM_MAP_COPY_ENTRY_LIST ; 
 TYPE_1__* VM_MAP_COPY_NULL ; 
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 TYPE_1__* vm_map_copy_allocate () ; 
 int /*<<< orphan*/  vm_map_copy_discard (TYPE_1__*) ; 
 scalar_t__ vm_map_remap_extract (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_store_init (TYPE_2__*) ; 
 scalar_t__ vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 

kern_return_t
vm_map_copy_extract(
	vm_map_t		src_map,
	vm_map_address_t	src_addr,
	vm_map_size_t		len,
	vm_map_copy_t		*copy_result,	/* OUT */
	vm_prot_t		*cur_prot,	/* OUT */
	vm_prot_t		*max_prot)
{
	vm_map_offset_t	src_start, src_end;
	vm_map_copy_t	copy;
	kern_return_t	kr;

	/*
	 *	Check for copies of zero bytes.
	 */

	if (len == 0) {
		*copy_result = VM_MAP_COPY_NULL;
		return(KERN_SUCCESS);
	}

	/*
	 *	Check that the end address doesn't overflow
	 */
	src_end = src_addr + len;
	if (src_end < src_addr)
		return KERN_INVALID_ADDRESS;

	/*
	 *	Compute (page aligned) start and end of region
	 */
	src_start = vm_map_trunc_page(src_addr, PAGE_MASK);
	src_end = vm_map_round_page(src_end, PAGE_MASK);

	/*
	 *	Allocate a header element for the list.
	 *
	 *	Use the start and end in the header to
	 *	remember the endpoints prior to rounding.
	 */

	copy = vm_map_copy_allocate();
	copy->type = VM_MAP_COPY_ENTRY_LIST;
	copy->cpy_hdr.entries_pageable = TRUE;

	vm_map_store_init(&copy->cpy_hdr);

	copy->offset = 0;
	copy->size = len;

	kr = vm_map_remap_extract(src_map,
				  src_addr,
				  len,
				  FALSE, /* copy */
				  &copy->cpy_hdr,
				  cur_prot,
				  max_prot,
				  VM_INHERIT_SHARE,
				  TRUE, /* pageable */
				  FALSE, /* same_map */
				  VM_MAP_KERNEL_FLAGS_NONE);
	if (kr != KERN_SUCCESS) {
		vm_map_copy_discard(copy);
		return kr;
	}

	*copy_result = copy;
	return KERN_SUCCESS;
}