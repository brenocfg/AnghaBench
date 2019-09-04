#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  scalar_t__ clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;
typedef  TYPE_1__* c_segment_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_14__ {int /*<<< orphan*/  count_of_swapouts; int /*<<< orphan*/  wasted_space_in_swapouts; int /*<<< orphan*/  count_of_freed_segs; } ;
struct TYPE_13__ {scalar_t__ c_state; scalar_t__ c_generation_id; int c_busy; scalar_t__ c_creation_ts; int /*<<< orphan*/  c_lock; scalar_t__ c_bytes_used; scalar_t__ c_overage_swap; int /*<<< orphan*/  c_on_minorcompact_q; int /*<<< orphan*/  c_age_list; } ;

/* Variables and functions */
 scalar_t__ C_ON_AGE_Q ; 
 int /*<<< orphan*/  C_ON_MAJORCOMPACT_Q ; 
 int /*<<< orphan*/  C_ON_SWAPOUT_Q ; 
 scalar_t__ C_SEG_BUFSIZE ; 
 int /*<<< orphan*/  C_SEG_BUSY (TYPE_1__*) ; 
 int /*<<< orphan*/  C_SEG_WAKEUP_DONE (TYPE_1__*) ; 
 scalar_t__ C_SWAPOUT_LIMIT ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_HIBERNATE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HIBLOG (char*) ; 
 int IOKDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  PAGE_REPLACEMENT_DISALLOWED (scalar_t__) ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_INTERRUPTIBLE ; 
 scalar_t__ TRUE ; 
 scalar_t__ VM_CONFIG_SWAP_IS_ACTIVE ; 
 int VM_CONFIG_SWAP_IS_PRESENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_wait_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  c_age_list_head ; 
 scalar_t__ c_generation_id_flush_barrier ; 
 int /*<<< orphan*/ * c_list_lock ; 
 scalar_t__ c_overage_swapped_count ; 
 scalar_t__ c_overage_swapped_limit ; 
 scalar_t__ c_seg_do_minor_compaction_and_unlock (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ c_seg_major_compact (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ c_seg_major_compact_ok (TYPE_1__*,TYPE_1__*) ; 
 TYPE_5__ c_seg_major_compact_stats ; 
 scalar_t__ c_seg_minor_compaction_and_unlock (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  c_seg_switch_state (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  c_seg_wait_on_busy (TYPE_1__*) ; 
 scalar_t__ c_segment_warmup_count ; 
 scalar_t__ c_swapout_count ; 
 int /*<<< orphan*/  c_swapout_list_head ; 
 int /*<<< orphan*/  c_swappedout_list_head ; 
 int /*<<< orphan*/  clock_get_system_nanotime (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ compaction_swapper_abort ; 
 int /*<<< orphan*/  compaction_swapper_running ; 
 scalar_t__ compressor_needs_to_swap () ; 
 int /*<<< orphan*/  do_fastwake_warmup (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ fastwake_warmup ; 
 scalar_t__ first_c_segment_to_warm_generation_id ; 
 scalar_t__ hibernate_flushing ; 
 scalar_t__ hibernate_flushing_deadline ; 
 scalar_t__ hibernate_in_progress_with_pinned_swap ; 
 scalar_t__ hibernate_no_swapspace ; 
 scalar_t__ hibernate_should_abort () ; 
 int /*<<< orphan*/  last_c_segment_to_warm_generation_id ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_compressor_age_swapped_in_segments (scalar_t__) ; 
 int /*<<< orphan*/  vm_compressor_do_delayed_compactions (scalar_t__) ; 
 int /*<<< orphan*/  vm_compressor_take_paging_space_action () ; 
 scalar_t__ vm_ripe_target_age ; 
 scalar_t__ vm_swap_files_pinned () ; 
 scalar_t__ vm_swap_low_on_space () ; 
 scalar_t__ vm_swapfile_total_segs_alloced ; 
 scalar_t__ vm_swapfile_total_segs_used ; 
 scalar_t__ vm_swapout_ripe_segments ; 

void
vm_compressor_compact_and_swap(boolean_t flush_all)
{
	c_segment_t	c_seg, c_seg_next;
	boolean_t	keep_compacting;
	clock_sec_t	now;
	clock_nsec_t	nsec;


	if (fastwake_warmup == TRUE) {
		uint64_t	starting_warmup_count;

		starting_warmup_count = c_segment_warmup_count;

		KERNEL_DEBUG_CONSTANT(IOKDBG_CODE(DBG_HIBERNATE, 11) | DBG_FUNC_START, c_segment_warmup_count,
				      first_c_segment_to_warm_generation_id, last_c_segment_to_warm_generation_id, 0, 0);
		do_fastwake_warmup(&c_swappedout_list_head, FALSE);
		KERNEL_DEBUG_CONSTANT(IOKDBG_CODE(DBG_HIBERNATE, 11) | DBG_FUNC_END, c_segment_warmup_count, c_segment_warmup_count - starting_warmup_count, 0, 0, 0);

		fastwake_warmup = FALSE;
	}

	/*
	 * it's possible for the c_age_list_head to be empty if we
	 * hit our limits for growing the compressor pool and we subsequently
	 * hibernated... on the next hibernation we could see the queue as
	 * empty and not proceeed even though we have a bunch of segments on
	 * the swapped in queue that need to be dealt with.
	 */
	vm_compressor_do_delayed_compactions(flush_all);

	vm_compressor_age_swapped_in_segments(flush_all);

	/*
	 * we only need to grab the timestamp once per
	 * invocation of this function since the 
	 * timescale we're interested in is measured
	 * in days
	 */
	clock_get_system_nanotime(&now,  &nsec);

	while (!queue_empty(&c_age_list_head) && compaction_swapper_abort == 0) {

		if (hibernate_flushing == TRUE) {
			clock_sec_t	sec;

			if (hibernate_should_abort()) {
				HIBLOG("vm_compressor_flush - hibernate_should_abort returned TRUE\n");
				break;
			}
			if (hibernate_no_swapspace == TRUE) {
				HIBLOG("vm_compressor_flush - out of swap space\n");
				break;
			}
			if (vm_swap_files_pinned() == FALSE) {
				HIBLOG("vm_compressor_flush - unpinned swap files\n");
				break;
			}
			if (hibernate_in_progress_with_pinned_swap == TRUE &&
			    (vm_swapfile_total_segs_alloced == vm_swapfile_total_segs_used)) {
				HIBLOG("vm_compressor_flush - out of pinned swap space\n");
				break;
			}
			clock_get_system_nanotime(&sec, &nsec);
		
			if (sec > hibernate_flushing_deadline) {
				HIBLOG("vm_compressor_flush - failed to finish before deadline\n");
				break;
			}
		}
		if (c_swapout_count >= C_SWAPOUT_LIMIT) {

			assert_wait_timeout((event_t) &compaction_swapper_running, THREAD_INTERRUPTIBLE, 100, 1000*NSEC_PER_USEC);

			lck_mtx_unlock_always(c_list_lock);

			thread_block(THREAD_CONTINUE_NULL);

			lck_mtx_lock_spin_always(c_list_lock);
		}
		/*
		 * Minor compactions
		 */
		vm_compressor_do_delayed_compactions(flush_all);

		vm_compressor_age_swapped_in_segments(flush_all);

		if (c_swapout_count >= C_SWAPOUT_LIMIT) {
			/*
			 * we timed out on the above thread_block
			 * let's loop around and try again
			 * the timeout allows us to continue
			 * to do minor compactions to make
			 * more memory available
			 */
			continue;
		}

		/*
		 * Swap out segments?
		 */
		if (flush_all == FALSE) {
			boolean_t	needs_to_swap;

			lck_mtx_unlock_always(c_list_lock);

			needs_to_swap = compressor_needs_to_swap();

#if !CONFIG_EMBEDDED
			if (needs_to_swap == TRUE && vm_swap_low_on_space())
				vm_compressor_take_paging_space_action();
#endif /* !CONFIG_EMBEDDED */

			lck_mtx_lock_spin_always(c_list_lock);
			
			if (needs_to_swap == FALSE)
				break;
		}
		if (queue_empty(&c_age_list_head))
			break;
		c_seg = (c_segment_t) queue_first(&c_age_list_head);

		assert(c_seg->c_state == C_ON_AGE_Q);

		if (flush_all == TRUE && c_seg->c_generation_id > c_generation_id_flush_barrier)
			break;
		
		lck_mtx_lock_spin_always(&c_seg->c_lock);

		if (c_seg->c_busy) {

			lck_mtx_unlock_always(c_list_lock);
			c_seg_wait_on_busy(c_seg);
			lck_mtx_lock_spin_always(c_list_lock);

			continue;
		}
		C_SEG_BUSY(c_seg);

		if (c_seg_do_minor_compaction_and_unlock(c_seg, FALSE, TRUE, TRUE)) {
			/*
			 * found an empty c_segment and freed it
			 * so go grab the next guy in the queue
			 */
			c_seg_major_compact_stats.count_of_freed_segs++;
			continue;
		}
		/*
		 * Major compaction
		 */
		keep_compacting = TRUE;

		while (keep_compacting == TRUE) {
					
			assert(c_seg->c_busy);

			/* look for another segment to consolidate */

			c_seg_next = (c_segment_t) queue_next(&c_seg->c_age_list);
			
			if (queue_end(&c_age_list_head, (queue_entry_t)c_seg_next))
				break;

			assert(c_seg_next->c_state == C_ON_AGE_Q);

			if (c_seg_major_compact_ok(c_seg, c_seg_next) == FALSE)
				break;

			lck_mtx_lock_spin_always(&c_seg_next->c_lock);

			if (c_seg_next->c_busy) {

				lck_mtx_unlock_always(c_list_lock);
				c_seg_wait_on_busy(c_seg_next);
				lck_mtx_lock_spin_always(c_list_lock);

				continue;
			}
			/* grab that segment */
			C_SEG_BUSY(c_seg_next);

			if (c_seg_do_minor_compaction_and_unlock(c_seg_next, FALSE, TRUE, TRUE)) {
				/*
				 * found an empty c_segment and freed it
				 * so we can't continue to use c_seg_next
				 */
				c_seg_major_compact_stats.count_of_freed_segs++;
				continue;
			}

			/* unlock the list ... */
			lck_mtx_unlock_always(c_list_lock);

			/* do the major compaction */

			keep_compacting = c_seg_major_compact(c_seg, c_seg_next);

			PAGE_REPLACEMENT_DISALLOWED(TRUE);

			lck_mtx_lock_spin_always(&c_seg_next->c_lock);
			/*
			 * run a minor compaction on the donor segment
			 * since we pulled at least some of it's 
			 * data into our target...  if we've emptied
			 * it, now is a good time to free it which
			 * c_seg_minor_compaction_and_unlock also takes care of
			 *
			 * by passing TRUE, we ask for c_busy to be cleared
			 * and c_wanted to be taken care of
			 */
			if (c_seg_minor_compaction_and_unlock(c_seg_next, TRUE))
				c_seg_major_compact_stats.count_of_freed_segs++;

			PAGE_REPLACEMENT_DISALLOWED(FALSE);

			/* relock the list */
			lck_mtx_lock_spin_always(c_list_lock);

		} /* major compaction */

		lck_mtx_lock_spin_always(&c_seg->c_lock);

		assert(c_seg->c_busy);
		assert(!c_seg->c_on_minorcompact_q);

		if (VM_CONFIG_SWAP_IS_ACTIVE) {
			/*
			 * This mode of putting a generic c_seg on the swapout list is
			 * only supported when we have general swapping enabled
			 */
			c_seg_switch_state(c_seg, C_ON_SWAPOUT_Q, FALSE);
		} else {
			if ((vm_swapout_ripe_segments == TRUE && c_overage_swapped_count < c_overage_swapped_limit)) {

				assert(VM_CONFIG_SWAP_IS_PRESENT);
				/*
				 * we are running compressor sweeps with swap-behind
				 * make sure the c_seg has aged enough before swapping it
				 * out...
				 */
				if ((now - c_seg->c_creation_ts) >= vm_ripe_target_age) {
					c_seg->c_overage_swap = TRUE;
					c_overage_swapped_count++;
					c_seg_switch_state(c_seg, C_ON_SWAPOUT_Q, FALSE);
				}
			}
		}
		if (c_seg->c_state == C_ON_AGE_Q) {
			/*
			 * this c_seg didn't get moved to the swapout queue
			 * so we need to move it out of the way...
			 * we just did a major compaction on it so put it
			 * on that queue
			 */ 
			c_seg_switch_state(c_seg, C_ON_MAJORCOMPACT_Q, FALSE);
		} else {
			c_seg_major_compact_stats.wasted_space_in_swapouts += C_SEG_BUFSIZE - c_seg->c_bytes_used;
			c_seg_major_compact_stats.count_of_swapouts++;
		}
		C_SEG_WAKEUP_DONE(c_seg);

		lck_mtx_unlock_always(&c_seg->c_lock);

		if (c_swapout_count) {
			lck_mtx_unlock_always(c_list_lock);

			thread_wakeup((event_t)&c_swapout_list_head);
			
			lck_mtx_lock_spin_always(c_list_lock);
		}
	}
}