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
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 uintptr_t LCK_ILOCK ; 
 scalar_t__ LCK_MTX_STATE_TO_THREAD (uintptr_t) ; 
 uintptr_t LCK_MTX_TAG_DESTROYED ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ not_in_kdp ; 
 uintptr_t ordered_load_mtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

boolean_t
kdp_lck_mtx_lock_spin_is_acquired(lck_mtx_t *lck)
{
	uintptr_t	state;

	if (not_in_kdp) {
		panic("panic: spinlock acquired check done outside of kernel debugger");
	}
	state = ordered_load_mtx(lck);
	if (state == LCK_MTX_TAG_DESTROYED)
		return FALSE;
	if (LCK_MTX_STATE_TO_THREAD(state) || (state & LCK_ILOCK))
		return TRUE;
	return FALSE;
}