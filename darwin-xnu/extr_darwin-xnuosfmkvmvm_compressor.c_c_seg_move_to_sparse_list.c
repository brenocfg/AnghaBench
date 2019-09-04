#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* c_segment_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  c_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_ON_SWAPPEDOUTSPARSE_Q ; 
 int /*<<< orphan*/  C_SEG_BUSY (TYPE_1__*) ; 
 int /*<<< orphan*/  C_SEG_WAKEUP_DONE (TYPE_1__*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * c_list_lock ; 
 int /*<<< orphan*/  c_seg_moved_to_sparse_list ; 
 int /*<<< orphan*/  c_seg_switch_state (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_try_lock_spin_always (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ *) ; 

void
c_seg_move_to_sparse_list(c_segment_t c_seg)
{
	boolean_t	clear_busy = FALSE;

	if ( !lck_mtx_try_lock_spin_always(c_list_lock)) {
		C_SEG_BUSY(c_seg);

		lck_mtx_unlock_always(&c_seg->c_lock);
		lck_mtx_lock_spin_always(c_list_lock);
		lck_mtx_lock_spin_always(&c_seg->c_lock);
		
		clear_busy = TRUE;
	}
	c_seg_switch_state(c_seg, C_ON_SWAPPEDOUTSPARSE_Q, FALSE);

	c_seg_moved_to_sparse_list++;

	lck_mtx_unlock_always(c_list_lock);

	if (clear_busy == TRUE)
		C_SEG_WAKEUP_DONE(c_seg);
}