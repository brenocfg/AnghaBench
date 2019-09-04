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
typedef  TYPE_1__* zone_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {scalar_t__ elem_size; } ;

/* Variables and functions */
 scalar_t__ ZP_POISON ; 
 scalar_t__ __improbable (int) ; 
 scalar_t__* get_backup_ptr (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  zone_element_was_modified_panic (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void
zalloc_poison_element(boolean_t check_poison, zone_t zone, vm_offset_t addr)
{
	vm_offset_t     inner_size = zone->elem_size;
	if (__improbable(check_poison && addr)) {
		vm_offset_t *element_cursor  = ((vm_offset_t *) addr) + 1;
		vm_offset_t *backup  = get_backup_ptr(inner_size, (vm_offset_t *) addr);

		for ( ; element_cursor < backup ; element_cursor++)
			if (__improbable(*element_cursor != ZP_POISON))
				zone_element_was_modified_panic(zone,
				                                addr,
				                                *element_cursor,
				                                ZP_POISON,
				                                ((vm_offset_t)element_cursor) - addr);
	}

	if (addr) {
		/*
		 * Clear out the old next pointer and backup to avoid leaking the cookie
		 * and so that only values on the freelist have a valid cookie
		 */

		vm_offset_t *primary  = (vm_offset_t *) addr;
		vm_offset_t *backup   = get_backup_ptr(inner_size, primary);

		*primary = ZP_POISON;
		*backup  = ZP_POISON;
	}
}