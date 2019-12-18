#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_map_t ;
struct TYPE_13__ {int lck_attr_val; } ;
struct TYPE_11__ {scalar_t__ nentries; } ;
struct TYPE_12__ {int min_offset; int max_offset; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  lock; scalar_t__ pmap; TYPE_1__ hdr; } ;

/* Variables and functions */
 int LCK_ATTR_DEBUG ; 
 int /*<<< orphan*/  VM_MAP_NULL ; 
 int VM_MAP_REMOVE_GAPS_OK ; 
 int VM_MAP_REMOVE_IMMUTABLE ; 
 int VM_MAP_REMOVE_NO_UNNESTING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_corpse_footprint_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_delete (TYPE_2__*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_disable_hole_optimization (TYPE_2__*) ; 
 TYPE_6__ vm_map_lck_attr ; 
 int /*<<< orphan*/  vm_map_lck_grp ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_2__*) ; 

void
vm_map_destroy(
	vm_map_t	map,
	int		flags)
{
	vm_map_lock(map);

	/* final cleanup: no need to unnest shared region */
	flags |= VM_MAP_REMOVE_NO_UNNESTING;
	/* final cleanup: ok to remove immutable mappings */
	flags |= VM_MAP_REMOVE_IMMUTABLE;
	/* final cleanup: allow gaps in range */
	flags |= VM_MAP_REMOVE_GAPS_OK;

	/* clean up regular map entries */
	(void) vm_map_delete(map, map->min_offset, map->max_offset,
			     flags, VM_MAP_NULL);
	/* clean up leftover special mappings (commpage, etc...) */
#if	!defined(__arm__) && !defined(__arm64__)
	(void) vm_map_delete(map, 0x0, 0xFFFFFFFFFFFFF000ULL,
			     flags, VM_MAP_NULL);
#endif /* !__arm__ && !__arm64__ */

	vm_map_disable_hole_optimization(map);
	vm_map_corpse_footprint_destroy(map);

	vm_map_unlock(map);

	assert(map->hdr.nentries == 0);

	if(map->pmap)
		pmap_destroy(map->pmap);

	if (vm_map_lck_attr.lck_attr_val & LCK_ATTR_DEBUG) {
		/*
		 * If lock debugging is enabled the mutexes get tagged as LCK_MTX_TAG_INDIRECT.
		 * And this is regardless of whether the lck_mtx_ext_t is embedded in the
		 * structure or kalloc'ed via lck_mtx_init.
		 * An example is s_lock_ext within struct _vm_map.
		 *
		 * A lck_mtx_destroy on such a mutex will attempt a kfree and panic. We
		 * can add another tag to detect embedded vs alloc'ed indirect external
		 * mutexes but that'll be additional checks in the lock path and require
		 * updating dependencies for the old vs new tag.
		 *
		 * Since the kfree() is for LCK_MTX_TAG_INDIRECT mutexes and that tag is applied
		 * just when lock debugging is ON, we choose to forego explicitly destroying
		 * the vm_map mutex and rw lock and, as a consequence, will overflow the reference
		 * count on vm_map_lck_grp, which has no serious side-effect.
		 */
	} else {
		lck_rw_destroy(&(map)->lock, &vm_map_lck_grp);
		lck_mtx_destroy(&(map)->s_lock, &vm_map_lck_grp);
	}

	zfree(vm_map_zone, map);
}