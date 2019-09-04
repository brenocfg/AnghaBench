#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  TYPE_1__* vm_map_copy_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int type; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  VM_MAP_COPY_ENTRY_LIST 130 
#define  VM_MAP_COPY_KERNEL_BUFFER 129 
 TYPE_1__* VM_MAP_COPY_NULL ; 
#define  VM_MAP_COPY_OBJECT 128 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_round_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
vm_map_copy_validate_size(
	vm_map_t		dst_map,
	vm_map_copy_t		copy,
	vm_map_size_t		*size)
{
	if (copy == VM_MAP_COPY_NULL)
		return FALSE;
	vm_map_size_t copy_sz = copy->size;
	vm_map_size_t sz = *size;
	switch (copy->type) {
	case VM_MAP_COPY_OBJECT:
	case VM_MAP_COPY_KERNEL_BUFFER:
		if (sz == copy_sz)
			return TRUE;
		break;
	case VM_MAP_COPY_ENTRY_LIST:
		/*
		 * potential page-size rounding prevents us from exactly
		 * validating this flavor of vm_map_copy, but we can at least
		 * assert that it's within a range.
		 */
		if (copy_sz >= sz &&
		    copy_sz <= vm_map_round_page(sz, VM_MAP_PAGE_MASK(dst_map))) {
			*size = copy_sz;
			return TRUE;
		}
		break;
	default:
		break;
	}
	return FALSE;
}