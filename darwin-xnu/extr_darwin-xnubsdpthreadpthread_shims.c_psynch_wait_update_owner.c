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

/* Variables and functions */
 int TURNSTILE_IMMEDIATE_UPDATE ; 
 int TURNSTILE_INHERITOR_THREAD ; 
 int /*<<< orphan*/  TURNSTILE_INTERLOCK_HELD ; 
 int /*<<< orphan*/  TURNSTILE_NULL ; 
 int /*<<< orphan*/  TURNSTILE_PTHREAD_MUTEX ; 
 int /*<<< orphan*/  turnstile_complete (uintptr_t,struct turnstile**,int /*<<< orphan*/ *) ; 
 struct turnstile* turnstile_prepare (uintptr_t,struct turnstile**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_update_inheritor (struct turnstile*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  turnstile_update_inheritor_complete (struct turnstile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
psynch_wait_update_owner(uintptr_t kwq, thread_t owner,
		struct turnstile **tstore)
{
	struct turnstile *ts;

	ts = turnstile_prepare(kwq, tstore, TURNSTILE_NULL,
			TURNSTILE_PTHREAD_MUTEX);

	turnstile_update_inheritor(ts, owner,
			(TURNSTILE_IMMEDIATE_UPDATE | TURNSTILE_INHERITOR_THREAD));
	turnstile_update_inheritor_complete(ts, TURNSTILE_INTERLOCK_HELD);
	turnstile_complete(kwq, tstore, NULL);
}