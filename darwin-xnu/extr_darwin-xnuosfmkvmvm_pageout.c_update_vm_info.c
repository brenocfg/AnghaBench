#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct TYPE_6__ {void* vm_pageout_considered_page; void* vm_pageout_compressions; void* vm_compressor_failed; void* vm_compressor_pages_grabbed; void* vm_phantom_cache_found_ghost; void* vm_phantom_cache_added_ghost; void* vm_page_pages_freed; void* vm_pageout_pages_evicted; void* vm_pageout_pages_purged; void* vm_pageout_freed_speculative; void* vm_pageout_freed_external; void* vm_pageout_inactive_referenced; void* vm_pageout_scan_inactive_throttled_external; void* vm_pageout_inactive_dirty_external; void* vm_pageout_freed_cleaned; void* vm_pageout_inactive_nolock; void* vm_pageout_scan_inactive_throttled_internal; void* vm_pageout_skipped_external; void* vm_pageout_reactivation_limit_exceeded; void* vm_pageout_inactive_force_reclaim; void* vm_pageout_freed_internal; void* vm_pageout_considered_bq_internal; void* vm_pageout_considered_bq_external; void* vm_pageout_filecache_min_reactivated; void* vm_pageout_inactive_dirty_internal; } ;
struct TYPE_5__ {int vm_page_active_count; unsigned int vm_page_speculative_count; unsigned int vm_page_inactive_count; unsigned int vm_page_anonymous_count; int vm_page_free_count; unsigned int vm_page_wire_count; unsigned int vm_page_compressor_count; int vm_page_pages_compressed; unsigned int vm_page_pageable_internal_count; unsigned int vm_page_pageable_external_count; unsigned int vm_page_xpmapped_external_count; unsigned int considered; unsigned int pages_compressed; unsigned int failed_compressions; unsigned int pages_grabbed_by_compressor; unsigned int phantom_ghosts_found; unsigned int phantom_ghosts_added; unsigned int pages_grabbed; unsigned int pages_freed; unsigned int pages_evicted; unsigned int pages_purged; unsigned int freed_speculative; unsigned int freed_external; unsigned int inactive_referenced; unsigned int throttled_external_q; unsigned int cleaned_dirty_external; unsigned int freed_cleaned; unsigned int inactive_nolock; unsigned int throttled_internal_q; unsigned int skipped_external; unsigned int reactivation_limit_exceeded; unsigned int forced_inactive_reclaim; unsigned int freed_internal; unsigned int considered_bq_internal; unsigned int considered_bq_external; unsigned int filecache_min_reactivations; unsigned int cleaned_dirty_internal; } ;
struct TYPE_4__ {void* vm_pageout_inactive_dirty_internal; void* vm_pageout_filecache_min_reactivated; void* vm_pageout_considered_bq_external; void* vm_pageout_considered_bq_internal; void* vm_pageout_freed_internal; void* vm_pageout_inactive_force_reclaim; void* vm_pageout_reactivation_limit_exceeded; void* vm_pageout_skipped_external; void* vm_pageout_scan_inactive_throttled_internal; void* vm_pageout_inactive_nolock; void* vm_pageout_freed_cleaned; void* vm_pageout_inactive_dirty_external; void* vm_pageout_scan_inactive_throttled_external; void* vm_pageout_inactive_referenced; void* vm_pageout_freed_external; void* vm_pageout_freed_speculative; void* vm_pageout_pages_purged; void* vm_pageout_pages_evicted; void* vm_page_pages_freed; void* vm_phantom_cache_added_ghost; void* vm_phantom_cache_found_ghost; void* vm_compressor_pages_grabbed; void* vm_compressor_failed; void* vm_pageout_compressions; void* vm_pageout_considered_page; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_VM ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_INFO1 ; 
 int /*<<< orphan*/  VM_INFO2 ; 
 int /*<<< orphan*/  VM_INFO3 ; 
 int /*<<< orphan*/  VM_INFO4 ; 
 int /*<<< orphan*/  VM_INFO5 ; 
 int /*<<< orphan*/  VM_INFO6 ; 
 int /*<<< orphan*/  VM_INFO7 ; 
 int /*<<< orphan*/  VM_INFO8 ; 
 int /*<<< orphan*/  VM_INFO9 ; 
 unsigned int VM_PAGE_COMPRESSOR_COUNT ; 
 int c_segment_pages_compressed ; 
 void* get_pages_grabbed_count () ; 
 TYPE_3__ last ; 
 void* last_vm_page_pages_grabbed ; 
 int /*<<< orphan*/  record_memory_pressure () ; 
 int vm_page_active_count ; 
 unsigned int vm_page_anonymous_count ; 
 int vm_page_free_count ; 
 unsigned int vm_page_inactive_count ; 
 unsigned int vm_page_pageable_external_count ; 
 unsigned int vm_page_pageable_internal_count ; 
 unsigned int vm_page_speculative_count ; 
 unsigned int vm_page_wire_count ; 
 unsigned int vm_page_xpmapped_external_count ; 
 size_t vm_pageout_stat_now ; 
 TYPE_2__* vm_pageout_stats ; 
 TYPE_1__ vm_pageout_vminfo ; 

void update_vm_info(void)
{
        uint64_t tmp;

	vm_pageout_stats[vm_pageout_stat_now].vm_page_active_count = vm_page_active_count;
	vm_pageout_stats[vm_pageout_stat_now].vm_page_speculative_count = vm_page_speculative_count;
	vm_pageout_stats[vm_pageout_stat_now].vm_page_inactive_count = vm_page_inactive_count;
	vm_pageout_stats[vm_pageout_stat_now].vm_page_anonymous_count = vm_page_anonymous_count;

	vm_pageout_stats[vm_pageout_stat_now].vm_page_free_count = vm_page_free_count;
	vm_pageout_stats[vm_pageout_stat_now].vm_page_wire_count = vm_page_wire_count;
	vm_pageout_stats[vm_pageout_stat_now].vm_page_compressor_count = VM_PAGE_COMPRESSOR_COUNT;

	vm_pageout_stats[vm_pageout_stat_now].vm_page_pages_compressed = c_segment_pages_compressed;
	vm_pageout_stats[vm_pageout_stat_now].vm_page_pageable_internal_count = vm_page_pageable_internal_count;
	vm_pageout_stats[vm_pageout_stat_now].vm_page_pageable_external_count = vm_page_pageable_external_count;
	vm_pageout_stats[vm_pageout_stat_now].vm_page_xpmapped_external_count = vm_page_xpmapped_external_count;


	tmp = vm_pageout_vminfo.vm_pageout_considered_page;
	vm_pageout_stats[vm_pageout_stat_now].considered = (unsigned int)(tmp - last.vm_pageout_considered_page);
	last.vm_pageout_considered_page = tmp;

	tmp = vm_pageout_vminfo.vm_pageout_compressions;
	vm_pageout_stats[vm_pageout_stat_now].pages_compressed = (unsigned int)(tmp - last.vm_pageout_compressions);
	last.vm_pageout_compressions = tmp;

	tmp = vm_pageout_vminfo.vm_compressor_failed;
	vm_pageout_stats[vm_pageout_stat_now].failed_compressions = (unsigned int)(tmp - last.vm_compressor_failed);
	last.vm_compressor_failed = tmp;

	tmp = vm_pageout_vminfo.vm_compressor_pages_grabbed;
	vm_pageout_stats[vm_pageout_stat_now].pages_grabbed_by_compressor = (unsigned int)(tmp - last.vm_compressor_pages_grabbed);
	last.vm_compressor_pages_grabbed = tmp;

	tmp = vm_pageout_vminfo.vm_phantom_cache_found_ghost;
	vm_pageout_stats[vm_pageout_stat_now].phantom_ghosts_found = (unsigned int)(tmp - last.vm_phantom_cache_found_ghost);
	last.vm_phantom_cache_found_ghost = tmp;

	tmp = vm_pageout_vminfo.vm_phantom_cache_added_ghost;
	vm_pageout_stats[vm_pageout_stat_now].phantom_ghosts_added = (unsigned int)(tmp - last.vm_phantom_cache_added_ghost);
	last.vm_phantom_cache_added_ghost = tmp;

	tmp = get_pages_grabbed_count();
	vm_pageout_stats[vm_pageout_stat_now].pages_grabbed = (unsigned int)(tmp - last_vm_page_pages_grabbed);
	last_vm_page_pages_grabbed = tmp;

	tmp = vm_pageout_vminfo.vm_page_pages_freed;
	vm_pageout_stats[vm_pageout_stat_now].pages_freed = (unsigned int)(tmp - last.vm_page_pages_freed);
	last.vm_page_pages_freed = tmp;


	if (vm_pageout_stats[vm_pageout_stat_now].considered) {

	        tmp = vm_pageout_vminfo.vm_pageout_pages_evicted;
		vm_pageout_stats[vm_pageout_stat_now].pages_evicted = (unsigned int)(tmp - last.vm_pageout_pages_evicted);
		last.vm_pageout_pages_evicted = tmp;

	        tmp = vm_pageout_vminfo.vm_pageout_pages_purged;
		vm_pageout_stats[vm_pageout_stat_now].pages_purged = (unsigned int)(tmp - last.vm_pageout_pages_purged);
		last.vm_pageout_pages_purged = tmp;

	        tmp = vm_pageout_vminfo.vm_pageout_freed_speculative;
		vm_pageout_stats[vm_pageout_stat_now].freed_speculative = (unsigned int)(tmp - last.vm_pageout_freed_speculative);
		last.vm_pageout_freed_speculative = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_freed_external;
		vm_pageout_stats[vm_pageout_stat_now].freed_external = (unsigned int)(tmp - last.vm_pageout_freed_external);
		last.vm_pageout_freed_external = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_inactive_referenced;
		vm_pageout_stats[vm_pageout_stat_now].inactive_referenced = (unsigned int)(tmp - last.vm_pageout_inactive_referenced);
		last.vm_pageout_inactive_referenced = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_scan_inactive_throttled_external;
		vm_pageout_stats[vm_pageout_stat_now].throttled_external_q = (unsigned int)(tmp - last.vm_pageout_scan_inactive_throttled_external);
		last.vm_pageout_scan_inactive_throttled_external = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_inactive_dirty_external;
		vm_pageout_stats[vm_pageout_stat_now].cleaned_dirty_external = (unsigned int)(tmp - last.vm_pageout_inactive_dirty_external);
		last.vm_pageout_inactive_dirty_external = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_freed_cleaned;
		vm_pageout_stats[vm_pageout_stat_now].freed_cleaned = (unsigned int)(tmp - last.vm_pageout_freed_cleaned);
		last.vm_pageout_freed_cleaned = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_inactive_nolock;
		vm_pageout_stats[vm_pageout_stat_now].inactive_nolock = (unsigned int)(tmp - last.vm_pageout_inactive_nolock);
		last.vm_pageout_inactive_nolock = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_scan_inactive_throttled_internal;
		vm_pageout_stats[vm_pageout_stat_now].throttled_internal_q = (unsigned int)(tmp - last.vm_pageout_scan_inactive_throttled_internal);
		last.vm_pageout_scan_inactive_throttled_internal = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_skipped_external;
		vm_pageout_stats[vm_pageout_stat_now].skipped_external = (unsigned int)(tmp - last.vm_pageout_skipped_external);
		last.vm_pageout_skipped_external = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_reactivation_limit_exceeded;
		vm_pageout_stats[vm_pageout_stat_now].reactivation_limit_exceeded = (unsigned int)(tmp - last.vm_pageout_reactivation_limit_exceeded);
		last.vm_pageout_reactivation_limit_exceeded = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_inactive_force_reclaim;
		vm_pageout_stats[vm_pageout_stat_now].forced_inactive_reclaim = (unsigned int)(tmp - last.vm_pageout_inactive_force_reclaim);
		last.vm_pageout_inactive_force_reclaim = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_freed_internal;
		vm_pageout_stats[vm_pageout_stat_now].freed_internal = (unsigned int)(tmp - last.vm_pageout_freed_internal);
		last.vm_pageout_freed_internal = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_considered_bq_internal;
		vm_pageout_stats[vm_pageout_stat_now].considered_bq_internal = (unsigned int)(tmp - last.vm_pageout_considered_bq_internal);
		last.vm_pageout_considered_bq_internal = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_considered_bq_external;
		vm_pageout_stats[vm_pageout_stat_now].considered_bq_external = (unsigned int)(tmp - last.vm_pageout_considered_bq_external);
		last.vm_pageout_considered_bq_external = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_filecache_min_reactivated;
		vm_pageout_stats[vm_pageout_stat_now].filecache_min_reactivations = (unsigned int)(tmp - last.vm_pageout_filecache_min_reactivated);
		last.vm_pageout_filecache_min_reactivated = tmp;

		tmp = vm_pageout_vminfo.vm_pageout_inactive_dirty_internal;
		vm_pageout_stats[vm_pageout_stat_now].cleaned_dirty_internal = (unsigned int)(tmp - last.vm_pageout_inactive_dirty_internal);
		last.vm_pageout_inactive_dirty_internal = tmp;
	}

	KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, VM_INFO1)) | DBG_FUNC_NONE,
			      vm_pageout_stats[vm_pageout_stat_now].vm_page_active_count,
			      vm_pageout_stats[vm_pageout_stat_now].vm_page_speculative_count,
			      vm_pageout_stats[vm_pageout_stat_now].vm_page_inactive_count,
			      vm_pageout_stats[vm_pageout_stat_now].vm_page_anonymous_count,
			      0);

	KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, VM_INFO2)) | DBG_FUNC_NONE,
			      vm_pageout_stats[vm_pageout_stat_now].vm_page_free_count,
			      vm_pageout_stats[vm_pageout_stat_now].vm_page_wire_count,
			      vm_pageout_stats[vm_pageout_stat_now].vm_page_compressor_count,
			      0,
			      0);

	KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, VM_INFO3)) | DBG_FUNC_NONE,
			      vm_pageout_stats[vm_pageout_stat_now].vm_page_pages_compressed,
			      vm_pageout_stats[vm_pageout_stat_now].vm_page_pageable_internal_count,
			      vm_pageout_stats[vm_pageout_stat_now].vm_page_pageable_external_count,
			      vm_pageout_stats[vm_pageout_stat_now].vm_page_xpmapped_external_count,
			      0);

	if (vm_pageout_stats[vm_pageout_stat_now].considered ||
	    vm_pageout_stats[vm_pageout_stat_now].pages_compressed ||
	    vm_pageout_stats[vm_pageout_stat_now].failed_compressions) {

		KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, VM_INFO4)) | DBG_FUNC_NONE,
				      vm_pageout_stats[vm_pageout_stat_now].considered,
				      vm_pageout_stats[vm_pageout_stat_now].freed_speculative,
				      vm_pageout_stats[vm_pageout_stat_now].freed_external,
				      vm_pageout_stats[vm_pageout_stat_now].inactive_referenced,
				      0);

		KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, VM_INFO5)) | DBG_FUNC_NONE,
				      vm_pageout_stats[vm_pageout_stat_now].throttled_external_q,
				      vm_pageout_stats[vm_pageout_stat_now].cleaned_dirty_external,
				      vm_pageout_stats[vm_pageout_stat_now].freed_cleaned,
				      vm_pageout_stats[vm_pageout_stat_now].inactive_nolock,
				      0);

		KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, VM_INFO6)) | DBG_FUNC_NONE,
				      vm_pageout_stats[vm_pageout_stat_now].throttled_internal_q,
				      vm_pageout_stats[vm_pageout_stat_now].pages_compressed,
				      vm_pageout_stats[vm_pageout_stat_now].pages_grabbed_by_compressor,
				      vm_pageout_stats[vm_pageout_stat_now].skipped_external,
				      0);

		KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, VM_INFO7)) | DBG_FUNC_NONE,
				      vm_pageout_stats[vm_pageout_stat_now].reactivation_limit_exceeded,
				      vm_pageout_stats[vm_pageout_stat_now].forced_inactive_reclaim,
				      vm_pageout_stats[vm_pageout_stat_now].failed_compressions,
				      vm_pageout_stats[vm_pageout_stat_now].freed_internal,
				      0);

		KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, VM_INFO8)) | DBG_FUNC_NONE,
				      vm_pageout_stats[vm_pageout_stat_now].considered_bq_internal,
				      vm_pageout_stats[vm_pageout_stat_now].considered_bq_external,
				      vm_pageout_stats[vm_pageout_stat_now].filecache_min_reactivations,
				      vm_pageout_stats[vm_pageout_stat_now].cleaned_dirty_internal,
				      0);

	}
	KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, VM_INFO9)) | DBG_FUNC_NONE,
			      vm_pageout_stats[vm_pageout_stat_now].pages_grabbed,
			      vm_pageout_stats[vm_pageout_stat_now].pages_freed,
			      vm_pageout_stats[vm_pageout_stat_now].phantom_ghosts_found,
			      vm_pageout_stats[vm_pageout_stat_now].phantom_ghosts_added,
			      0);

	record_memory_pressure();
}