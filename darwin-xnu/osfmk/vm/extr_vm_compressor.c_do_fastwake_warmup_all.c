#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  c_list_lock ; 
 int /*<<< orphan*/  c_swappedout_list_head ; 
 int /*<<< orphan*/  c_swappedout_sparse_list_head ; 
 int /*<<< orphan*/  do_fastwake_warmup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fastwake_warmup ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock_always (int /*<<< orphan*/ ) ; 
 scalar_t__ queue_empty (int /*<<< orphan*/ *) ; 

void
do_fastwake_warmup_all(void)
{

	lck_mtx_lock_spin_always(c_list_lock);

	if (queue_empty(&c_swappedout_list_head) && queue_empty(&c_swappedout_sparse_list_head)) {

		lck_mtx_unlock_always(c_list_lock);
		return;
	}

	fastwake_warmup = TRUE;

	do_fastwake_warmup(&c_swappedout_list_head, TRUE);

	do_fastwake_warmup(&c_swappedout_sparse_list_head, TRUE);

	fastwake_warmup = FALSE;

	lck_mtx_unlock_always(c_list_lock);

}