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
struct turnstile {int /*<<< orphan*/  ts_waitq; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_recompute_priority_locked (struct turnstile*) ; 
 int /*<<< orphan*/  waitq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_unlock (int /*<<< orphan*/ *) ; 

boolean_t
turnstile_recompute_priority(
	struct turnstile *turnstile)
{
	boolean_t needs_priority_update = FALSE;
	spl_t s = splsched();

	waitq_lock(&turnstile->ts_waitq);

	needs_priority_update = turnstile_recompute_priority_locked(turnstile);

	waitq_unlock(&turnstile->ts_waitq);
	splx(s);
	return needs_priority_update;

}