#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;
typedef  TYPE_1__* c_segment_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {scalar_t__ c_creation_ts; } ;

/* Variables and functions */
 int COMPRESSOR_FREE_RESERVED_LIMIT ; 
 scalar_t__ COMPRESSOR_NEEDS_TO_SWAP () ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ VM_CONFIG_SWAP_IS_ACTIVE ; 
 scalar_t__ VM_PAGE_Q_THROTTLED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_age_list_head ; 
 int /*<<< orphan*/  c_list_lock ; 
 scalar_t__ c_overage_swapped_count ; 
 scalar_t__ c_overage_swapped_limit ; 
 int /*<<< orphan*/  clock_get_system_nanotime (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compressor_thrashing_induced_jetsam ; 
 int /*<<< orphan*/  compute_swapout_target_age () ; 
 int /*<<< orphan*/  filecache_thrashing_induced_jetsam ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memorystatus_kill_on_FC_thrashing (scalar_t__) ; 
 int /*<<< orphan*/  memorystatus_kill_on_VM_compressor_space_shortage (scalar_t__) ; 
 int /*<<< orphan*/  memorystatus_kill_on_VM_compressor_thrashing (scalar_t__) ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ swapout_target_age ; 
 scalar_t__ vm_compressor_low_on_space () ; 
 scalar_t__ vm_compressor_needs_to_major_compact () ; 
 scalar_t__ vm_compressor_thrashing_detected ; 
 int vm_page_anonymous_count ; 
 int vm_page_free_count ; 
 int vm_page_free_reserved ; 
 int vm_page_inactive_count ; 
 int /*<<< orphan*/  vm_pageout_queue_external ; 
 scalar_t__ vm_phantom_cache_check_pressure () ; 
 scalar_t__ vm_ripe_target_age ; 
 scalar_t__ vm_swapout_ripe_segments ; 

__attribute__((used)) static boolean_t
compressor_needs_to_swap(void)
{
	boolean_t	should_swap = FALSE;

	if (vm_swapout_ripe_segments == TRUE && c_overage_swapped_count < c_overage_swapped_limit) {
		c_segment_t	c_seg;
		clock_sec_t	now;
		clock_sec_t	age;
		clock_nsec_t	nsec;
		
		clock_get_system_nanotime(&now,  &nsec);
		age = 0;

		lck_mtx_lock_spin_always(c_list_lock);

		if ( !queue_empty(&c_age_list_head)) {
			c_seg = (c_segment_t) queue_first(&c_age_list_head);

			age = now - c_seg->c_creation_ts;
		}
		lck_mtx_unlock_always(c_list_lock);

		if (age >= vm_ripe_target_age)
			return (TRUE);
	}
	if (VM_CONFIG_SWAP_IS_ACTIVE) {
		if (COMPRESSOR_NEEDS_TO_SWAP()) {
			return (TRUE);
		}
		if (VM_PAGE_Q_THROTTLED(&vm_pageout_queue_external) && vm_page_anonymous_count < (vm_page_inactive_count / 20)) {
			return (TRUE);
		}
		if (vm_page_free_count < (vm_page_free_reserved - (COMPRESSOR_FREE_RESERVED_LIMIT * 2)))
			return (TRUE);
	}
	compute_swapout_target_age();
			
	if (swapout_target_age) {
		c_segment_t	c_seg;

		lck_mtx_lock_spin_always(c_list_lock);

		if (!queue_empty(&c_age_list_head)) {

			c_seg = (c_segment_t) queue_first(&c_age_list_head);

			if (c_seg->c_creation_ts > swapout_target_age)
				swapout_target_age = 0;
		}
		lck_mtx_unlock_always(c_list_lock);
	}
#if CONFIG_PHANTOM_CACHE
	if (vm_phantom_cache_check_pressure())
		should_swap = TRUE;
#endif
	if (swapout_target_age)
		should_swap = TRUE;

#if CONFIG_JETSAM
	if (should_swap || vm_compressor_low_on_space() == TRUE) {

		if (vm_compressor_thrashing_detected == FALSE) {
			vm_compressor_thrashing_detected = TRUE;
				
			if (swapout_target_age || vm_compressor_low_on_space() == TRUE) {
				if (swapout_target_age) {
					/* The compressor is thrashing. */
					memorystatus_kill_on_VM_compressor_thrashing(TRUE /* async */);
				} else {
					/* The compressor is running low on space. */
					memorystatus_kill_on_VM_compressor_space_shortage(TRUE /* async */);
				}
				compressor_thrashing_induced_jetsam++;
			} else {
				memorystatus_kill_on_FC_thrashing(TRUE /* async */);
				filecache_thrashing_induced_jetsam++;
			}
		}
		/*
		 * let the jetsam take precedence over
		 * any major compactions we might have
		 * been able to do... otherwise we run
		 * the risk of doing major compactions
		 * on segments we're about to free up
		 * due to the jetsam activity.
		 */
		should_swap = FALSE;
	}

#endif /* CONFIG_JETSAM */

	if (should_swap == FALSE) {
		/*
		 * vm_compressor_needs_to_major_compact returns true only if we're
		 * about to run out of available compressor segments... in this
		 * case, we absolutely need to run a major compaction even if
		 * we've just kicked off a jetsam or we don't otherwise need to
		 * swap... terminating objects releases
		 * pages back to the uncompressed cache, but does not guarantee
		 * that we will free up even a single compression segment
		 */
		should_swap = vm_compressor_needs_to_major_compact();
	}

	/*
	 * returning TRUE when swap_supported == FALSE
	 * will cause the major compaction engine to
	 * run, but will not trigger any swapping...
	 * segments that have been major compacted
	 * will be moved to the majorcompact queue
	 */
	return (should_swap);
}