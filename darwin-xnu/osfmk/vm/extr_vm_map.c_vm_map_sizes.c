#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  int boolean_t ;
struct TYPE_11__ {scalar_t__ vme_end; scalar_t__ vme_start; struct TYPE_11__* vme_next; } ;
struct TYPE_10__ {scalar_t__ max_offset; scalar_t__ min_offset; } ;

/* Variables and functions */
 TYPE_2__* vm_map_first_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_lock_read (TYPE_1__*) ; 
 TYPE_2__* vm_map_to_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock_read (TYPE_1__*) ; 

void
vm_map_sizes(vm_map_t map,
		vm_map_size_t * psize,
		vm_map_size_t * pfree,
		vm_map_size_t * plargest_free)
{
    vm_map_entry_t  entry;
    vm_map_offset_t prev;
    vm_map_size_t   free, total_free, largest_free;
    boolean_t       end;

    if (!map)
    {
        *psize = *pfree = *plargest_free = 0;
        return;
    }
    total_free = largest_free = 0;

    vm_map_lock_read(map);
    if (psize) *psize = map->max_offset - map->min_offset;

    prev = map->min_offset;
    for (entry = vm_map_first_entry(map);; entry = entry->vme_next)
    {
	end = (entry == vm_map_to_entry(map));

	if (end) free = entry->vme_end   - prev;
	else     free = entry->vme_start - prev;

	total_free += free;
	if (free > largest_free) largest_free = free;

	if (end) break;
	prev = entry->vme_end;
    }
    vm_map_unlock_read(map);
    if (pfree)         *pfree = total_free;
    if (plargest_free) *plargest_free = largest_free;
}