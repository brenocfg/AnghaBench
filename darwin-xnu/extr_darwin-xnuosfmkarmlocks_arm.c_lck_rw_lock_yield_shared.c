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
struct TYPE_2__ {scalar_t__ want_upgrade; scalar_t__ want_excl; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ lck_rw_word_t ;
typedef  int /*<<< orphan*/  lck_rw_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_SHARED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  lck_rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_unlock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_pause (int) ; 
 int /*<<< orphan*/  ordered_load_rw (int /*<<< orphan*/ *) ; 

boolean_t
lck_rw_lock_yield_shared(lck_rw_t *lck, boolean_t force_yield)
{
	lck_rw_word_t	word;

	lck_rw_assert(lck, LCK_RW_ASSERT_SHARED);

	word.data = ordered_load_rw(lck);
	if (word.want_excl || word.want_upgrade || force_yield) {
		lck_rw_unlock_shared(lck);
		mutex_pause(2);
		lck_rw_lock_shared(lck);
		return TRUE;
	}

	return FALSE;
}