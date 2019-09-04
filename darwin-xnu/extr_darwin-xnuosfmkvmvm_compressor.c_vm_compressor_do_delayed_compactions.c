#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* c_segment_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {scalar_t__ c_busy; int /*<<< orphan*/  c_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_SEG_BUSY (TYPE_1__*) ; 
 scalar_t__ C_SWAPOUT_LIMIT ; 
 int /*<<< orphan*/  DELAYED_COMPACTIONS_PER_PASS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ TRUE ; 
 scalar_t__ VM_CONFIG_SWAP_IS_ACTIVE ; 
 int /*<<< orphan*/ * c_list_lock ; 
 int /*<<< orphan*/  c_minor_list_head ; 
 int /*<<< orphan*/  c_seg_do_minor_compaction_and_unlock (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  c_seg_wait_on_busy (TYPE_1__*) ; 
 scalar_t__ c_swapout_count ; 
 scalar_t__ compressor_needs_to_swap () ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 

void
vm_compressor_do_delayed_compactions(boolean_t flush_all)
{
	c_segment_t	c_seg;
	int		number_compacted = 0;
	boolean_t	needs_to_swap = FALSE;


#if !CONFIG_EMBEDDED
	LCK_MTX_ASSERT(c_list_lock, LCK_MTX_ASSERT_OWNED);
#endif /* !CONFIG_EMBEDDED */

	while (!queue_empty(&c_minor_list_head) && needs_to_swap == FALSE) {
		
		c_seg = (c_segment_t)queue_first(&c_minor_list_head);
		
		lck_mtx_lock_spin_always(&c_seg->c_lock);

		if (c_seg->c_busy) {

			lck_mtx_unlock_always(c_list_lock);
			c_seg_wait_on_busy(c_seg);
			lck_mtx_lock_spin_always(c_list_lock);

			continue;
		}
		C_SEG_BUSY(c_seg);

		c_seg_do_minor_compaction_and_unlock(c_seg, TRUE, FALSE, TRUE);

		if (VM_CONFIG_SWAP_IS_ACTIVE && (number_compacted++ > DELAYED_COMPACTIONS_PER_PASS)) {
			
			if ((flush_all == TRUE || compressor_needs_to_swap() == TRUE) && c_swapout_count < C_SWAPOUT_LIMIT)
				needs_to_swap = TRUE;

			number_compacted = 0;
		}
		lck_mtx_lock_spin_always(c_list_lock);
	}
}