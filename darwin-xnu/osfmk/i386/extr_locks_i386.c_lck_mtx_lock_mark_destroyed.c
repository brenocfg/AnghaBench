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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_TAG_DESTROYED ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  lck_mtx_interlock_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_load_mtx_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_store_mtx_state_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lck_mtx_lock_mark_destroyed(
	lck_mtx_t *mutex,
	boolean_t indirect)
{
	uint32_t state;

	if (indirect) {
		/* convert to destroyed state */
		ordered_store_mtx_state_release(mutex, LCK_MTX_TAG_DESTROYED);
		return;
	}

	state = ordered_load_mtx_state(mutex);
	lck_mtx_interlock_lock(mutex, &state);

	ordered_store_mtx_state_release(mutex, LCK_MTX_TAG_DESTROYED);

	enable_preemption();
}