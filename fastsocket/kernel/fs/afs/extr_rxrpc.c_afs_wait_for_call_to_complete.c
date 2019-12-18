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
struct sk_buff {int dummy; } ;
struct afs_call {int error; scalar_t__ state; TYPE_1__* type; int /*<<< orphan*/ * rxcall; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  waitq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destructor ) (struct afs_call*) ;} ;

/* Variables and functions */
 scalar_t__ AFS_CALL_COMPLETE ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int /*<<< orphan*/  RX_CALL_DEAD ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  afs_deliver_to_call (struct afs_call*) ; 
 int /*<<< orphan*/  afs_free_call (struct afs_call*) ; 
 int /*<<< orphan*/  afs_free_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  myself ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_kernel_abort_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_kernel_end_call (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct afs_call*) ; 

__attribute__((used)) static int afs_wait_for_call_to_complete(struct afs_call *call)
{
	struct sk_buff *skb;
	int ret;

	DECLARE_WAITQUEUE(myself, current);

	_enter("");

	add_wait_queue(&call->waitq, &myself);
	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);

		/* deliver any messages that are in the queue */
		if (!skb_queue_empty(&call->rx_queue)) {
			__set_current_state(TASK_RUNNING);
			afs_deliver_to_call(call);
			continue;
		}

		ret = call->error;
		if (call->state >= AFS_CALL_COMPLETE)
			break;
		ret = -EINTR;
		if (signal_pending(current))
			break;
		schedule();
	}

	remove_wait_queue(&call->waitq, &myself);
	__set_current_state(TASK_RUNNING);

	/* kill the call */
	if (call->state < AFS_CALL_COMPLETE) {
		_debug("call incomplete");
		rxrpc_kernel_abort_call(call->rxcall, RX_CALL_DEAD);
		while ((skb = skb_dequeue(&call->rx_queue)))
			afs_free_skb(skb);
	}

	_debug("call complete");
	rxrpc_kernel_end_call(call->rxcall);
	call->rxcall = NULL;
	call->type->destructor(call);
	afs_free_call(call);
	_leave(" = %d", ret);
	return ret;
}