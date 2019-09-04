#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;
typedef  TYPE_2__* c_segment_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/ * c_buffer; } ;
struct TYPE_8__ {scalar_t__ c_overage_swap; scalar_t__ c_swappedin_ts; int /*<<< orphan*/  c_populated_offset; TYPE_1__ c_store; int /*<<< orphan*/  c_on_minorcompact_q; scalar_t__ c_busy_swapping; scalar_t__ c_busy; int /*<<< orphan*/  c_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_ON_AGE_Q ; 
 int /*<<< orphan*/  C_ON_BAD_Q ; 
 int /*<<< orphan*/  C_ON_SWAPPEDIN_Q ; 
 int /*<<< orphan*/  C_SEG_BYTES_TO_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ C_SEG_UNUSED_BYTES (TYPE_2__*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/ * c_list_lock ; 
 int /*<<< orphan*/  c_overage_swapped_count ; 
 int /*<<< orphan*/  c_seg_need_delayed_compaction (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  c_seg_switch_state (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clock_get_system_nanotime (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ *) ; 

void
c_seg_swapin_requeue(c_segment_t c_seg, boolean_t has_data, boolean_t minor_compact_ok, boolean_t age_on_swapin_q)
{
        clock_sec_t	sec;
        clock_nsec_t	nsec;

	clock_get_system_nanotime(&sec, &nsec);

	lck_mtx_lock_spin_always(c_list_lock);
	lck_mtx_lock_spin_always(&c_seg->c_lock);

	assert(c_seg->c_busy_swapping);
	assert(c_seg->c_busy);

	c_seg->c_busy_swapping = 0;

	if (c_seg->c_overage_swap == TRUE) {
		c_overage_swapped_count--;
		c_seg->c_overage_swap = FALSE;
	}	
	if (has_data == TRUE) {
		if (age_on_swapin_q == TRUE)
			c_seg_switch_state(c_seg, C_ON_SWAPPEDIN_Q, FALSE);
		else
			c_seg_switch_state(c_seg, C_ON_AGE_Q, FALSE);

		if (minor_compact_ok == TRUE && !c_seg->c_on_minorcompact_q && C_SEG_UNUSED_BYTES(c_seg) >= PAGE_SIZE)
			c_seg_need_delayed_compaction(c_seg, TRUE);
	} else {
		c_seg->c_store.c_buffer = (int32_t*) NULL;
		c_seg->c_populated_offset = C_SEG_BYTES_TO_OFFSET(0);

		c_seg_switch_state(c_seg, C_ON_BAD_Q, FALSE);
	}
	c_seg->c_swappedin_ts = (uint32_t)sec;

	lck_mtx_unlock_always(c_list_lock);
}