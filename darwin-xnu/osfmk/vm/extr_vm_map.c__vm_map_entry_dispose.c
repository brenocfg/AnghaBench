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
typedef  scalar_t__ zone_t ;
typedef  TYPE_1__* vm_map_entry_t ;
struct vm_map_header {scalar_t__ entries_pageable; } ;
struct TYPE_4__ {int /*<<< orphan*/  from_reserved_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonreserved_zalloc_count ; 
 int /*<<< orphan*/  reserved_zalloc_count ; 
 scalar_t__ vm_map_entry_reserved_zone ; 
 scalar_t__ vm_map_entry_zone ; 
 int /*<<< orphan*/  zfree (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static void
_vm_map_entry_dispose(
	struct vm_map_header	*map_header,
	vm_map_entry_t		entry)
{
	zone_t		zone;

	if (map_header->entries_pageable || !(entry->from_reserved_zone))
		zone = vm_map_entry_zone;
	else
		zone = vm_map_entry_reserved_zone;

	if (!map_header->entries_pageable) {
		if (zone == vm_map_entry_zone)
			OSAddAtomic(-1, &nonreserved_zalloc_count);
		else
			OSAddAtomic(-1, &reserved_zalloc_count);
	}

	zfree(zone, entry);
}