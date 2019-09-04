#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;
typedef  TYPE_1__* c_segment_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {scalar_t__ c_swappedin_ts; int /*<<< orphan*/  c_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_ON_AGE_Q ; 
 scalar_t__ C_SEGMENT_SWAPPEDIN_AGE_LIMIT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  c_seg_switch_state (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  c_swappedin_list_head ; 
 int /*<<< orphan*/  clock_get_system_nanotime (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vm_compressor_age_swapped_in_segments(boolean_t flush_all)
{
	c_segment_t	c_seg;
	clock_sec_t	now;
	clock_nsec_t	nsec;

	clock_get_system_nanotime(&now,  &nsec);
			
	while (!queue_empty(&c_swappedin_list_head)) {

		c_seg = (c_segment_t)queue_first(&c_swappedin_list_head);

		if (flush_all == FALSE && (now - c_seg->c_swappedin_ts) < C_SEGMENT_SWAPPEDIN_AGE_LIMIT)
			break;
			
		lck_mtx_lock_spin_always(&c_seg->c_lock);

		c_seg_switch_state(c_seg, C_ON_AGE_Q, FALSE);

		lck_mtx_unlock_always(&c_seg->c_lock);
	}
}