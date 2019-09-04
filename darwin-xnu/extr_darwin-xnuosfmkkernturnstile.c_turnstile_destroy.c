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
struct turnstile {scalar_t__ ts_inheritor; int ts_state; int /*<<< orphan*/  ts_free_turnstiles; int /*<<< orphan*/  ts_waitq; } ;

/* Variables and functions */
 int SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ TURNSTILE_INHERITOR_NULL ; 
 int TURNSTILE_STATE_THREAD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  turnstiles_zone ; 
 int /*<<< orphan*/  waitq_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct turnstile*) ; 

void
turnstile_destroy(struct turnstile *turnstile)
{
	/* destroy the waitq */
	waitq_deinit(&turnstile->ts_waitq);

	assert(turnstile->ts_inheritor == TURNSTILE_INHERITOR_NULL);
	assert(SLIST_EMPTY(&turnstile->ts_free_turnstiles));
	assert(turnstile->ts_state & TURNSTILE_STATE_THREAD);
#if DEVELOPMENT || DEBUG
	/* Remove turnstile from global list */
	global_turnstiles_lock();
	queue_remove(&turnstiles_list, turnstile,
		struct turnstile *, ts_global_elm);
	global_turnstiles_unlock();
#endif
	zfree(turnstiles_zone, turnstile);
}