#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct binder_transaction {struct binder_transaction* from_parent; struct binder_thread* from; struct binder_transaction* to_parent; TYPE_1__* buffer; struct binder_thread* to_thread; int /*<<< orphan*/ * to_proc; int /*<<< orphan*/  debug_id; } ;
struct binder_thread {int /*<<< orphan*/  todo; int /*<<< orphan*/  pid; struct binder_transaction* transaction_stack; int /*<<< orphan*/  rb_node; } ;
struct binder_proc {int /*<<< orphan*/  pid; int /*<<< orphan*/  threads; } ;
struct TYPE_2__ {int /*<<< orphan*/ * transaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEBUG_DEAD_TRANSACTION ; 
 int /*<<< orphan*/  BINDER_STAT_THREAD ; 
 int /*<<< orphan*/  BR_DEAD_REPLY ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  binder_release_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_send_failed_reply (struct binder_transaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_stats_deleted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct binder_thread*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int binder_free_thread(struct binder_proc *proc,
			      struct binder_thread *thread)
{
	struct binder_transaction *t;
	struct binder_transaction *send_reply = NULL;
	int active_transactions = 0;

	rb_erase(&thread->rb_node, &proc->threads);
	t = thread->transaction_stack;
	if (t && t->to_thread == thread)
		send_reply = t;
	while (t) {
		active_transactions++;
		binder_debug(BINDER_DEBUG_DEAD_TRANSACTION,
			     "binder: release %d:%d transaction %d "
			     "%s, still active\n", proc->pid, thread->pid,
			     t->debug_id,
			     (t->to_thread == thread) ? "in" : "out");

		if (t->to_thread == thread) {
			t->to_proc = NULL;
			t->to_thread = NULL;
			if (t->buffer) {
				t->buffer->transaction = NULL;
				t->buffer = NULL;
			}
			t = t->to_parent;
		} else if (t->from == thread) {
			t->from = NULL;
			t = t->from_parent;
		} else
			BUG();
	}
	if (send_reply)
		binder_send_failed_reply(send_reply, BR_DEAD_REPLY);
	binder_release_work(&thread->todo);
	kfree(thread);
	binder_stats_deleted(BINDER_STAT_THREAD);
	return active_transactions;
}