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
typedef  int turnstile_stats_update_flags_t ;
struct turnstile {int ts_inheritor_flags; int /*<<< orphan*/  ts_waitq; struct turnstile* ts_inheritor; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int TSU_NO_INHERITOR ; 
 int TSU_NO_PRI_CHANGE_NEEDED ; 
 int TSU_TURNSTILE_ARG ; 
 int TURNSTILE_INHERITOR_TURNSTILE ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int turnstile_need_turnstile_promotion_update (struct turnstile*,struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_stats_update (int,int,struct turnstile*) ; 
 int turnstile_update_turnstile_promotion_locked (struct turnstile*,struct turnstile*) ; 
 int /*<<< orphan*/  waitq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
turnstile_update_inheritor_turnstile_priority_chain(
	struct turnstile **in_out_turnstile,
	int total_hop,
	turnstile_stats_update_flags_t tsu_flags)
{
	boolean_t needs_update = FALSE;
	struct turnstile *turnstile = *in_out_turnstile;
	struct turnstile *inheritor_turnstile = turnstile->ts_inheritor;
	boolean_t first_update = !total_hop;

	assert(turnstile->ts_inheritor_flags & TURNSTILE_INHERITOR_TURNSTILE);
	*in_out_turnstile = TURNSTILE_NULL;

	/* Check if the inheritor turnstile needs to be updated before grabbing the lock */
	needs_update = turnstile_need_turnstile_promotion_update(inheritor_turnstile, turnstile);
	if (!needs_update && !first_update) {
		turnstile_stats_update(total_hop + 1, TSU_NO_PRI_CHANGE_NEEDED |
			TSU_TURNSTILE_ARG | tsu_flags,
			turnstile);
		waitq_unlock(&turnstile->ts_waitq);
		return;
	}

	waitq_lock(&inheritor_turnstile->ts_waitq);

	needs_update = turnstile_update_turnstile_promotion_locked(
		inheritor_turnstile, turnstile);

	/*
	 * Check if turnstile needs further priority propagation,
	 * since the first hop priority update was done in
	 * turnstile_update_inheritor, do not bailout if it is
	 * the first update as needs_update flag would evaluate to
	 * false for that case.
	 */
	if (!needs_update && !first_update) {
		/* Update turnstile stats before returning */
		turnstile_stats_update(total_hop + 1,
			(inheritor_turnstile->ts_inheritor ? TSU_NO_PRI_CHANGE_NEEDED : TSU_NO_INHERITOR) |
			TSU_TURNSTILE_ARG | tsu_flags,
			turnstile);
		waitq_unlock(&inheritor_turnstile->ts_waitq);
		waitq_unlock(&turnstile->ts_waitq);
		return;
	}

	/* Unlock the outer turnstile and update the inner turnstile */
	waitq_unlock(&turnstile->ts_waitq);
	*in_out_turnstile = inheritor_turnstile;
	return;
}