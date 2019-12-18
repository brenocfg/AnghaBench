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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  mutex_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LCK_MTX_MLOCKED_MSK ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  lck_mtx_interlock_try_lock_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_load_mtx_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_store_mtx_owner (int /*<<< orphan*/ *,uintptr_t) ; 

__attribute__((used)) static inline boolean_t
lck_mtx_lock_grab_mutex(
	lck_mtx_t 	*lock)
{
	uint32_t state;

	state = ordered_load_mtx_state(lock);

	if (!lck_mtx_interlock_try_lock_set_flags(lock, LCK_MTX_MLOCKED_MSK, &state)) {
		return FALSE;
	}

	/* lock and interlock acquired */

	thread_t thread = current_thread();
	/* record owner of mutex */
	ordered_store_mtx_owner(lock, (uintptr_t)thread);

#if MACH_LDEBUG
	if (thread) {
		thread->mutex_count++;		/* lock statistic */
	}
#endif
	return TRUE;
}