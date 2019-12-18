#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ulk_addr; scalar_t__ ulk_pid; } ;
struct TYPE_7__ {scalar_t__ ull_nwaiters; scalar_t__ ull_owner; scalar_t__ ull_refcount; TYPE_1__ ull_key; } ;
typedef  TYPE_2__ ull_t ;
typedef  scalar_t__ thread_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  thread_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  turnstile_cleanup () ; 
 int /*<<< orphan*/  ull_assert_owned (TYPE_2__*) ; 
 int /*<<< orphan*/  ull_put (TYPE_2__*) ; 

__attribute__((used)) static void
ulock_wait_cleanup(ull_t *ull, thread_t owner_thread, thread_t old_owner, int32_t *retval)
{
	ull_assert_owned(ull);

	thread_t old_lingering_owner = THREAD_NULL;

	*retval = --ull->ull_nwaiters;
	if (ull->ull_nwaiters == 0) {
		/*
		 * If the wait was canceled early, we might need to
		 * clear out the lingering owner reference before
		 * freeing the ull.
		 */
		old_lingering_owner = ull->ull_owner;
		ull->ull_owner = THREAD_NULL;

		ull->ull_key.ulk_pid = 0;
		ull->ull_key.ulk_addr = 0;
		ull->ull_refcount--;
		assert(ull->ull_refcount > 0);
	}
	ull_put(ull);

	/* Need to be called after dropping the interlock */
	turnstile_cleanup();

	if (owner_thread != THREAD_NULL) {
		thread_deallocate(owner_thread);
	}

	if (old_owner != THREAD_NULL) {
		thread_deallocate(old_owner);
	}

	if (old_lingering_owner != THREAD_NULL) {
		thread_deallocate(old_lingering_owner);
	}

	assert(*retval >= 0);
}