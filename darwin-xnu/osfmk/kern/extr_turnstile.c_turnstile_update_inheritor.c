#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int turnstile_update_flags_t ;
typedef  scalar_t__ turnstile_inheritor_t ;
typedef  TYPE_1__* thread_t ;
struct workqueue {int dummy; } ;
struct turnstile {int /*<<< orphan*/  ts_waitq; } ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_4__ {scalar_t__ inheritor; int inheritor_flags; } ;

/* Variables and functions */
 int TURNSTILE_DELAYED_UPDATE ; 
 scalar_t__ TURNSTILE_INHERITOR_NULL ; 
 int TURNSTILE_INHERITOR_THREAD ; 
 int TURNSTILE_INHERITOR_TURNSTILE ; 
 int TURNSTILE_INHERITOR_WORKQ ; 
 int TURNSTILE_UPDATE_FLAGS_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  panic (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  turnstile_reference (struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_update_inheritor_locked (struct turnstile*) ; 
 int /*<<< orphan*/  waitq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  workq_reference (struct workqueue*) ; 

void
turnstile_update_inheritor(
	struct turnstile *turnstile,
	turnstile_inheritor_t new_inheritor,
	turnstile_update_flags_t flags)
{
	thread_t thread = current_thread();
	spl_t spl;

	/*
	 * Set the inheritor on calling thread struct, no need
	 * to take the turnstile waitq lock since the inheritor
	 * is protected by the primitive's interlock
	 */
	assert(thread->inheritor == TURNSTILE_INHERITOR_NULL);
	thread->inheritor = new_inheritor;
	thread->inheritor_flags = TURNSTILE_UPDATE_FLAGS_NONE;
	if (new_inheritor == TURNSTILE_INHERITOR_NULL) {
		/* nothing to retain or remember */
	} else if (flags & TURNSTILE_INHERITOR_THREAD) {
		thread->inheritor_flags |= TURNSTILE_INHERITOR_THREAD;
		thread_reference((thread_t)new_inheritor);
	} else if (flags & TURNSTILE_INHERITOR_TURNSTILE) {
		thread->inheritor_flags |= TURNSTILE_INHERITOR_TURNSTILE;
		turnstile_reference((struct turnstile *)new_inheritor);
	} else if (flags & TURNSTILE_INHERITOR_WORKQ) {
		thread->inheritor_flags |= TURNSTILE_INHERITOR_WORKQ;
		workq_reference((struct workqueue *)new_inheritor);
	} else {
		panic("Missing type in flags (%x) for inheritor (%p)", flags,
				new_inheritor);
	}

	/* Do not perform the update if delayed update is specified */
	if (flags & TURNSTILE_DELAYED_UPDATE) {
		return;
	}

	/* lock the turnstile waitq */
	spl = splsched();
	waitq_lock(&turnstile->ts_waitq);

	turnstile_update_inheritor_locked(turnstile);

	waitq_unlock(&turnstile->ts_waitq);
	splx(spl);

	return;
}