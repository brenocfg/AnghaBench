#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ vm_address_t ;
typedef  TYPE_1__* upl_t ;
typedef  scalar_t__ upl_size_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_10__ {int flags; int ref_count; scalar_t__ kaddr; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int MAX_VECTOR_UPL_ELEMENTS ; 
 TYPE_1__* UPL_NULL ; 
 int UPL_PAGE_LIST_MAPPED ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_REMOVE_NO_FLAGS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  panic (char*,int,int) ; 
 int /*<<< orphan*/  upl_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  upl_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vector_upl_get_submap (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int vector_upl_is_valid (TYPE_1__*) ; 
 TYPE_1__* vector_upl_subupl_byindex (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_map_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 

kern_return_t
vm_map_remove_upl(
	vm_map_t	map,
	upl_t		upl)
{
	vm_address_t	addr;
	upl_size_t	size;
	int		isVectorUPL = 0, curr_upl = 0;
	upl_t		vector_upl = NULL;

	if (upl == UPL_NULL)
		return KERN_INVALID_ARGUMENT;

	if((isVectorUPL = vector_upl_is_valid(upl))) {
		int 	unmapped=0, valid_upls=0;
		vector_upl = upl;
		upl_lock(vector_upl);
		for(curr_upl=0; curr_upl < MAX_VECTOR_UPL_ELEMENTS; curr_upl++) {
			upl =  vector_upl_subupl_byindex(vector_upl, curr_upl );
			if(upl == NULL)
				continue;
			valid_upls++;
			if (!(UPL_PAGE_LIST_MAPPED & upl->flags))
				unmapped++;
		}

		if(unmapped) {
			if(unmapped != valid_upls)
				panic("%d of the %d sub-upls within the Vector UPL is/are not mapped\n", unmapped, valid_upls);
			else {
				upl_unlock(vector_upl);
				return KERN_FAILURE;
			}
		}
		curr_upl=0;
	}
	else
		upl_lock(upl);

process_upl_to_remove:
	if(isVectorUPL) {
		if(curr_upl == MAX_VECTOR_UPL_ELEMENTS) {
			vm_map_t v_upl_submap;
			vm_offset_t v_upl_submap_dst_addr;
			vector_upl_get_submap(vector_upl, &v_upl_submap, &v_upl_submap_dst_addr);

			vm_map_remove(map, v_upl_submap_dst_addr, v_upl_submap_dst_addr + vector_upl->size, VM_MAP_REMOVE_NO_FLAGS);
			vm_map_deallocate(v_upl_submap);
			upl_unlock(vector_upl);
			return KERN_SUCCESS;
		}

		upl =  vector_upl_subupl_byindex(vector_upl, curr_upl++ );
		if(upl == NULL)
			goto process_upl_to_remove;
	}

	if (upl->flags & UPL_PAGE_LIST_MAPPED) {
		addr = upl->kaddr;
		size = upl->size;

		assert(upl->ref_count > 1);
		upl->ref_count--;		/* removing mapping ref */

		upl->flags &= ~UPL_PAGE_LIST_MAPPED;
		upl->kaddr = (vm_offset_t) 0;

		if(!isVectorUPL) {
			upl_unlock(upl);

			vm_map_remove(
				map,
				vm_map_trunc_page(addr,
						  VM_MAP_PAGE_MASK(map)),
				vm_map_round_page(addr + size,
						  VM_MAP_PAGE_MASK(map)),
				VM_MAP_REMOVE_NO_FLAGS);
			return KERN_SUCCESS;
		}
		else {
			/*
			* If it's a Vectored UPL, we'll be removing the entire
			* submap anyways, so no need to remove individual UPL
			* element mappings from within the submap
			*/
			goto process_upl_to_remove;
		}
	}
	upl_unlock(upl);

	return KERN_FAILURE;
}