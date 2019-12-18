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
struct work_struct {int dummy; } ;
struct sk_buff {int dummy; } ;
struct rxrpc_call {int dummy; } ;
struct afs_call {struct rxrpc_call* rxcall; TYPE_1__* type; int /*<<< orphan*/  state; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  waitq; int /*<<< orphan*/ * wait_mode; int /*<<< orphan*/  async_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CALL_AWAIT_OP_ID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct rxrpc_call*) ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 TYPE_1__ afs_RXCMxxxx ; 
 int /*<<< orphan*/  afs_async_incoming_call ; 
 int /*<<< orphan*/  afs_free_call (struct afs_call*) ; 
 int /*<<< orphan*/  afs_free_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  afs_incoming_calls ; 
 int /*<<< orphan*/  afs_outstanding_calls ; 
 int /*<<< orphan*/  afs_process_async_call ; 
 int /*<<< orphan*/  afs_socket ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct afs_call* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct rxrpc_call* rxrpc_kernel_accept_call (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  rxrpc_kernel_reject_call (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_collect_incoming_call(struct work_struct *work)
{
	struct rxrpc_call *rxcall;
	struct afs_call *call = NULL;
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&afs_incoming_calls))) {
		_debug("new call");

		/* don't need the notification */
		afs_free_skb(skb);

		if (!call) {
			call = kzalloc(sizeof(struct afs_call), GFP_KERNEL);
			if (!call) {
				rxrpc_kernel_reject_call(afs_socket);
				return;
			}

			INIT_WORK(&call->async_work, afs_process_async_call);
			call->wait_mode = &afs_async_incoming_call;
			call->type = &afs_RXCMxxxx;
			init_waitqueue_head(&call->waitq);
			skb_queue_head_init(&call->rx_queue);
			call->state = AFS_CALL_AWAIT_OP_ID;

			_debug("CALL %p{%s} [%d]",
			       call, call->type->name,
			       atomic_read(&afs_outstanding_calls));
			atomic_inc(&afs_outstanding_calls);
		}

		rxcall = rxrpc_kernel_accept_call(afs_socket,
						  (unsigned long) call);
		if (!IS_ERR(rxcall)) {
			call->rxcall = rxcall;
			call = NULL;
		}
	}

	if (call)
		afs_free_call(call);
}