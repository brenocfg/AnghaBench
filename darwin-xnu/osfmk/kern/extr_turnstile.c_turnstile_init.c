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
struct turnstile {int /*<<< orphan*/ * ts_prev_thread; int /*<<< orphan*/  ts_thread; int /*<<< orphan*/  ts_inheritor_queue; scalar_t__ ts_port_ref; int /*<<< orphan*/  ts_inheritor_flags; int /*<<< orphan*/  ts_priority; int /*<<< orphan*/  ts_proprietor; int /*<<< orphan*/  ts_refcount; scalar_t__ ts_type_gencount; int /*<<< orphan*/  ts_free_turnstiles; int /*<<< orphan*/  ts_inheritor; int /*<<< orphan*/  ts_waitq; } ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MAXPRI_THROTTLE ; 
 int /*<<< orphan*/  PRIORITY_QUEUE_BUILTIN_MAX_HEAP ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int SYNC_POLICY_DISABLE_IRQ ; 
 int SYNC_POLICY_REVERSED ; 
 int SYNC_POLICY_TURNSTILE ; 
 int /*<<< orphan*/  TURNSTILE_INHERITOR_NULL ; 
 int /*<<< orphan*/  TURNSTILE_NONE ; 
 int /*<<< orphan*/  TURNSTILE_PROPRIETOR_NULL ; 
 int /*<<< orphan*/  TURNSTILE_STATE_THREAD ; 
 int /*<<< orphan*/  TURNSTILE_UPDATE_FLAGS_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  os_ref_init_count (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  priority_queue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_refgrp ; 
 int /*<<< orphan*/  turnstile_set_type_and_increment_gencount (struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_state_init (struct turnstile*,int /*<<< orphan*/ ) ; 
 scalar_t__ waitq_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
turnstile_init(struct turnstile *turnstile)
{
	kern_return_t kret;

	/* Initialize the waitq */
	kret = waitq_init(&turnstile->ts_waitq, SYNC_POLICY_DISABLE_IRQ | SYNC_POLICY_REVERSED |
		SYNC_POLICY_TURNSTILE);
	assert(kret == KERN_SUCCESS);

	turnstile->ts_inheritor = TURNSTILE_INHERITOR_NULL;
	SLIST_INIT(&turnstile->ts_free_turnstiles);
	turnstile->ts_type_gencount = 0;
	turnstile_set_type_and_increment_gencount(turnstile, TURNSTILE_NONE);
	turnstile_state_init(turnstile, TURNSTILE_STATE_THREAD);
	os_ref_init_count(&turnstile->ts_refcount, &turnstile_refgrp, 1);
	turnstile->ts_proprietor = TURNSTILE_PROPRIETOR_NULL;
	turnstile->ts_priority = MAXPRI_THROTTLE;
	turnstile->ts_inheritor_flags = TURNSTILE_UPDATE_FLAGS_NONE;
	turnstile->ts_port_ref = 0;
	priority_queue_init(&turnstile->ts_inheritor_queue,
			PRIORITY_QUEUE_BUILTIN_MAX_HEAP);

#if DEVELOPMENT || DEBUG
	turnstile->ts_thread = current_thread();
	turnstile->ts_prev_thread = NULL;
#endif
}