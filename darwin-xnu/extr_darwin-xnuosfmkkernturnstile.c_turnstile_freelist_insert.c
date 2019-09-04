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
struct turnstile {scalar_t__ ts_proprietor; int /*<<< orphan*/  ts_free_turnstiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TURNSTILE_STATE_FREELIST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ts_free_elm ; 
 scalar_t__ turnstile_get_type (struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_state_add (struct turnstile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
turnstile_freelist_insert(
	struct turnstile *dst_ts,
	struct turnstile *free_ts)
{
	assert(turnstile_get_type(dst_ts) == turnstile_get_type(free_ts));
	assert(dst_ts->ts_proprietor == free_ts->ts_proprietor);
	turnstile_state_add(free_ts, TURNSTILE_STATE_FREELIST);
	SLIST_INSERT_HEAD(&dst_ts->ts_free_turnstiles, free_ts, ts_free_elm);
}