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
typedef  int /*<<< orphan*/  thread_continue_t ;
struct turnstile {int dummy; } ;
struct knote_lock_ctx {int dummy; } ;
struct _kevent_register {int /*<<< orphan*/  handoff_thread; int /*<<< orphan*/  knote; int /*<<< orphan*/  kq; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_KQ_UNLOCK ; 
 int /*<<< orphan*/  TURNSTILE_INTERLOCK_NOT_HELD ; 
 int /*<<< orphan*/  knote_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct knote_lock_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_handoff_parameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _kevent_register*) ; 
 int /*<<< orphan*/  turnstile_update_inheritor_complete (struct turnstile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kevent_register_wait_block(struct turnstile *ts, thread_t thread,
		struct knote_lock_ctx *knlc, thread_continue_t cont,
		struct _kevent_register *cont_args)
{
	knote_unlock(cont_args->kq, cont_args->knote, knlc, KNOTE_KQ_UNLOCK);
	turnstile_update_inheritor_complete(ts, TURNSTILE_INTERLOCK_NOT_HELD);
	cont_args->handoff_thread = thread;
	thread_handoff_parameter(thread, cont, cont_args);
}