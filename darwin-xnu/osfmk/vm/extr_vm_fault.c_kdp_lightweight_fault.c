#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_offset_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  TYPE_3__* vm_map_t ;
typedef  TYPE_4__* vm_map_entry_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_21__ {int vme_start; scalar_t__ is_sub_map; } ;
struct TYPE_20__ {int /*<<< orphan*/  lock; } ;
struct TYPE_19__ {int wimg_bits; int paging_offset; int vo_shadow_offset; struct TYPE_19__* shadow; int /*<<< orphan*/  pager; scalar_t__ pager_created; scalar_t__ activity_in_progress; scalar_t__ paging_in_progress; int /*<<< orphan*/  Lock; } ;
struct TYPE_18__ {scalar_t__ vmp_q_state; scalar_t__ vmp_fictitious; scalar_t__ vmp_private; scalar_t__ vmp_unusual; scalar_t__ vmp_restart; scalar_t__ vmp_overwriting; scalar_t__ vmp_cleaning; scalar_t__ vmp_error; scalar_t__ vmp_absent; scalar_t__ vmp_free_when_done; scalar_t__ vmp_busy; scalar_t__ vmp_laundry; } ;

/* Variables and functions */
 int C_DONT_BLOCK ; 
 int C_KDP ; 
 int C_KEEP ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MUST_ASK_PAGER (TYPE_2__*,int,int) ; 
 int PAGE_MASK ; 
 scalar_t__ TRUE ; 
 TYPE_2__* VME_OBJECT (TYPE_4__*) ; 
 int VME_OFFSET (TYPE_4__*) ; 
 int VM_EXTERNAL_STATE_EXISTS ; 
 int VM_EXTERNAL_STATE_UNKNOWN ; 
 TYPE_3__* VM_MAP_NULL ; 
 TYPE_2__* VM_OBJECT_NULL ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 TYPE_1__* VM_PAGE_NULL ; 
 scalar_t__ VM_PAGE_USED_BY_COMPRESSOR ; 
 int VM_PROT_READ ; 
 int VM_WIMG_DEFAULT ; 
 int VM_WIMG_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int kdp_compressor_decompressed_page_paddr ; 
 int /*<<< orphan*/  kdp_compressor_decompressed_page_ppnum ; 
 scalar_t__ kdp_lck_rw_lock_is_acquired_exclusive (int /*<<< orphan*/ *) ; 
 TYPE_1__* kdp_vm_page_lookup (TYPE_2__*,int) ; 
 scalar_t__ not_in_kdp ; 
 int /*<<< orphan*/  panic (char*) ; 
 int ptoa (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_compressor_pager_get (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int,int*) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (TYPE_3__*,int,TYPE_4__**) ; 

vm_offset_t
kdp_lightweight_fault(vm_map_t map, vm_offset_t cur_target_addr)
{
	vm_map_entry_t	entry;
	vm_object_t	object;
	vm_offset_t	object_offset;
	vm_page_t	m;
	int		compressor_external_state, compressed_count_delta;
	int		compressor_flags = (C_DONT_BLOCK | C_KEEP | C_KDP);
	int		my_fault_type = VM_PROT_READ;
	kern_return_t	kr;

	if (not_in_kdp) {
		panic("kdp_lightweight_fault called from outside of debugger context");
	}

	assert(map != VM_MAP_NULL);

	assert((cur_target_addr & PAGE_MASK) == 0);
	if ((cur_target_addr & PAGE_MASK) != 0) {
		return 0;
	}

	if (kdp_lck_rw_lock_is_acquired_exclusive(&map->lock)) {
		return 0;
	}

	if (!vm_map_lookup_entry(map, cur_target_addr, &entry)) {
		return 0;
	}

	if (entry->is_sub_map) {
		return 0;
	}

	object = VME_OBJECT(entry);
	if (object == VM_OBJECT_NULL) {
		return 0;
	}

	object_offset = cur_target_addr - entry->vme_start + VME_OFFSET(entry);

	while (TRUE) {
		if (kdp_lck_rw_lock_is_acquired_exclusive(&object->Lock)) {
			return 0;
		}

		if (object->pager_created && (object->paging_in_progress ||
			object->activity_in_progress)) {
			return 0;
		}

		m = kdp_vm_page_lookup(object, object_offset);

		if (m != VM_PAGE_NULL) {

			if ((object->wimg_bits & VM_WIMG_MASK) != VM_WIMG_DEFAULT) {
				return 0;
			}

			if (m->vmp_laundry || m->vmp_busy || m->vmp_free_when_done || m->vmp_absent || m->vmp_error || m->vmp_cleaning ||
				m->vmp_overwriting || m->vmp_restart || m->vmp_unusual) {
				return 0;
			}

			assert(!m->vmp_private);
			if (m->vmp_private) {
				return 0;
			}

			assert(!m->vmp_fictitious);
			if (m->vmp_fictitious) {
				return 0;
			}

			assert(m->vmp_q_state != VM_PAGE_USED_BY_COMPRESSOR);
			if (m->vmp_q_state == VM_PAGE_USED_BY_COMPRESSOR) {
				return 0;
			}

			return ptoa(VM_PAGE_GET_PHYS_PAGE(m));
		}

		compressor_external_state = VM_EXTERNAL_STATE_UNKNOWN;

		if (object->pager_created && MUST_ASK_PAGER(object, object_offset, compressor_external_state)) {
			if (compressor_external_state == VM_EXTERNAL_STATE_EXISTS) {
				kr = vm_compressor_pager_get(object->pager, (object_offset + object->paging_offset),
								kdp_compressor_decompressed_page_ppnum, &my_fault_type,
								compressor_flags, &compressed_count_delta);
				if (kr == KERN_SUCCESS) {
					return kdp_compressor_decompressed_page_paddr;
				} else {
					return 0;
				}
			}
		}

		if (object->shadow == VM_OBJECT_NULL) {
			return 0;
		}

		object_offset += object->vo_shadow_offset;
		object = object->shadow;
	}

}