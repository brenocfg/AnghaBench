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
typedef  int /*<<< orphan*/  wait_result_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct turnstile {int /*<<< orphan*/  ts_waitq; } ;
typedef  int /*<<< orphan*/  event_t ;
typedef  int /*<<< orphan*/  event64_t ;
typedef  int /*<<< orphan*/  block_hint_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_ABORTSAFE ; 
 int /*<<< orphan*/  TIMEOUT_URGENCY_USER_NORMAL ; 
 int TURNSTILE_DELAYED_UPDATE ; 
 int TURNSTILE_INHERITOR_THREAD ; 
 int /*<<< orphan*/  TURNSTILE_NULL ; 
 int /*<<< orphan*/  TURNSTILE_PTHREAD_MUTEX ; 
 int /*<<< orphan*/  assert_wait_deadline_with_leeway (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  thread_set_pending_block_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct turnstile* turnstile_prepare (uintptr_t,struct turnstile**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_update_inheritor (struct turnstile*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  waitq_assert_wait64_leeway (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static wait_result_t
psynch_wait_prepare(uintptr_t kwq, struct turnstile **tstore,
		thread_t owner, block_hint_t block_hint, uint64_t deadline)
{
	struct turnstile *ts;
	wait_result_t wr;

	if (tstore) {
		ts = turnstile_prepare(kwq, tstore, TURNSTILE_NULL,
				TURNSTILE_PTHREAD_MUTEX);

		turnstile_update_inheritor(ts, owner,
				(TURNSTILE_DELAYED_UPDATE | TURNSTILE_INHERITOR_THREAD));

		thread_set_pending_block_hint(current_thread(), block_hint);

		wr = waitq_assert_wait64_leeway(&ts->ts_waitq, (event64_t)kwq,
				THREAD_ABORTSAFE, TIMEOUT_URGENCY_USER_NORMAL, deadline, 0);
	} else {
		thread_set_pending_block_hint(current_thread(), block_hint);

		wr = assert_wait_deadline_with_leeway((event_t)kwq, THREAD_ABORTSAFE,
				TIMEOUT_URGENCY_USER_NORMAL, deadline, 0);
	}

	return wr;
}