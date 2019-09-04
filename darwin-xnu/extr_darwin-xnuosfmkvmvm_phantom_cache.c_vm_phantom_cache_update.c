#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  TYPE_3__* vm_ghost_t ;
struct TYPE_16__ {int /*<<< orphan*/  pcs_updated_phantom_state; } ;
struct TYPE_15__ {int /*<<< orphan*/  vm_phantom_cache_found_ghost; } ;
struct TYPE_14__ {int g_pages_held; } ;
struct TYPE_13__ {scalar_t__ phantom_isssd; } ;
struct TYPE_12__ {size_t vmp_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 size_t PAGE_SHIFT ; 
 size_t VM_GHOST_PAGE_MASK ; 
 TYPE_2__* VM_PAGE_OBJECT (TYPE_1__*) ; 
 int* pg_masks ; 
 TYPE_9__ phantom_cache_stats ; 
 int /*<<< orphan*/  sample_period_ghost_found_count ; 
 int /*<<< orphan*/  sample_period_ghost_found_count_ssd ; 
 int /*<<< orphan*/  vm_object_lock_assert_exclusive (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_queue_lock ; 
 TYPE_7__ vm_pageout_vminfo ; 
 TYPE_3__* vm_phantom_cache_lookup_ghost (TYPE_1__*,int) ; 
 scalar_t__ vm_phantom_cache_num_entries ; 

void
vm_phantom_cache_update(vm_page_t m)
{
	int		pg_mask;
	vm_ghost_t      vpce;
	vm_object_t	object;

	object = VM_PAGE_OBJECT(m);

	LCK_MTX_ASSERT(&vm_page_queue_lock, LCK_MTX_ASSERT_OWNED);
	vm_object_lock_assert_exclusive(object);

	if (vm_phantom_cache_num_entries == 0)
		return;
	
	pg_mask = pg_masks[(m->vmp_offset >> PAGE_SHIFT) & VM_GHOST_PAGE_MASK];
	
	if ( (vpce = vm_phantom_cache_lookup_ghost(m, pg_mask)) ) {

		vpce->g_pages_held &= ~pg_mask;

		phantom_cache_stats.pcs_updated_phantom_state++;
		vm_pageout_vminfo.vm_phantom_cache_found_ghost++;

		if (object->phantom_isssd)
			OSAddAtomic(1, &sample_period_ghost_found_count_ssd);
		else
			OSAddAtomic(1, &sample_period_ghost_found_count);
	}
}