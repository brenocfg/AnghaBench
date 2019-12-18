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
struct turnstile {int /*<<< orphan*/  ts_free_turnstiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct turnstile* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  TURNSTILE_STATE_FREELIST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ts_free_elm ; 
 int /*<<< orphan*/  turnstile_state_remove (struct turnstile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct turnstile *
turnstile_freelist_remove(
	struct turnstile *ts)
{
	struct turnstile *ret_turnstile = TURNSTILE_NULL;
	assert(!SLIST_EMPTY(&ts->ts_free_turnstiles));
	ret_turnstile = SLIST_FIRST(&ts->ts_free_turnstiles);
	SLIST_REMOVE_HEAD(&ts->ts_free_turnstiles, ts_free_elm);
	assert(ret_turnstile != TURNSTILE_NULL);
	turnstile_state_remove(ret_turnstile, TURNSTILE_STATE_FREELIST);
	/* Need to initialize the list again, since head and elm are in union */
	SLIST_INIT(&ret_turnstile->ts_free_turnstiles);
	return ret_turnstile;
}