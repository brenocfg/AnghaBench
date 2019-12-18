#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  TYPE_3__* vm_ghost_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  pcs_lookup_entry_not_in_cache; int /*<<< orphan*/  pcs_lookup_page_not_in_entry; int /*<<< orphan*/  pcs_lookup_found_page_in_cache; } ;
struct TYPE_12__ {int g_obj_id; scalar_t__ g_obj_offset; int g_pages_held; int g_next_index; } ;
struct TYPE_11__ {int phantom_object_id; } ;
struct TYPE_10__ {scalar_t__ vmp_offset; } ;

/* Variables and functions */
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ VM_GHOST_OFFSET_MASK ; 
 scalar_t__ VM_GHOST_PAGE_SHIFT ; 
 TYPE_2__* VM_PAGE_OBJECT (TYPE_1__*) ; 
 TYPE_7__ phantom_cache_stats ; 
 TYPE_3__* vm_phantom_cache ; 
 int* vm_phantom_cache_hash ; 
 size_t vm_phantom_hash (int,scalar_t__) ; 

vm_ghost_t
vm_phantom_cache_lookup_ghost(vm_page_t m, uint32_t pg_mask)
{
	uint64_t	g_obj_offset;
	uint32_t	g_obj_id;
	uint32_t	ghost_index;
	vm_object_t	object;

	object = VM_PAGE_OBJECT(m);

	if ((g_obj_id = object->phantom_object_id) == 0) {
		/*
		 * no entries in phantom cache for this object
		 */
		return (NULL);
	}
	g_obj_offset = (m->vmp_offset >> (PAGE_SHIFT + VM_GHOST_PAGE_SHIFT)) & VM_GHOST_OFFSET_MASK;

	ghost_index = vm_phantom_cache_hash[vm_phantom_hash(g_obj_id, g_obj_offset)];

	while (ghost_index) {
		vm_ghost_t      vpce;

		vpce = &vm_phantom_cache[ghost_index];

		if (vpce->g_obj_id == g_obj_id && vpce->g_obj_offset == g_obj_offset) {

			if (pg_mask == 0 || (vpce->g_pages_held & pg_mask)) {
				phantom_cache_stats.pcs_lookup_found_page_in_cache++;

				return (vpce);
			}
			phantom_cache_stats.pcs_lookup_page_not_in_entry++;

			return (NULL);
		}
		ghost_index = vpce->g_next_index;
	}
	phantom_cache_stats.pcs_lookup_entry_not_in_cache++;

	return (NULL);
}