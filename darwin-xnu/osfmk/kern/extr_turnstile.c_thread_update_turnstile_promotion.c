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
typedef  int /*<<< orphan*/  thread_t ;
struct turnstile {int dummy; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int TSU_BOOST_ARG ; 
 int TSU_NO_PRI_CHANGE_NEEDED ; 
 int TSU_TURNSTILE_ARG ; 
 int thread_get_update_flags_for_turnstile_propagation_stoppage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_needs_turnstile_promotion_update (int /*<<< orphan*/ ,struct turnstile*) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_update_turnstile_promotion_locked (int /*<<< orphan*/ ,struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_stats_update (int,int,struct turnstile*) ; 

__attribute__((used)) static boolean_t
thread_update_turnstile_promotion(
	thread_t thread,
	struct turnstile *turnstile)
{
	/* Before grabbing the thread lock, check if update is needed */
	boolean_t needs_update = thread_needs_turnstile_promotion_update(thread, turnstile);

	if (!needs_update) {
		turnstile_stats_update(1, TSU_NO_PRI_CHANGE_NEEDED |
			TSU_TURNSTILE_ARG | TSU_BOOST_ARG, turnstile);
		return needs_update;
	}

	/* Update the pairing heap */
	thread_lock(thread);
	needs_update = thread_update_turnstile_promotion_locked(thread, turnstile);

	/* Update turnstile stats */
	if (!needs_update) {
		turnstile_stats_update(1,
			thread_get_update_flags_for_turnstile_propagation_stoppage(thread) |
			TSU_TURNSTILE_ARG | TSU_BOOST_ARG,
			turnstile);
	}
	thread_unlock(thread);
	return needs_update;
}