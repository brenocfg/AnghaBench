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
struct rxrpc_call {int acks_winsz; int rx_data_expect; int /*<<< orphan*/  creation_jif; scalar_t__ rx_data_eaten; scalar_t__ ackr_win_top; scalar_t__ rx_first_oos; int /*<<< orphan*/  sock_node; int /*<<< orphan*/  state; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  usage; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_waitq; int /*<<< orphan*/  rx_oos_queue; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  accept_link; int /*<<< orphan*/  processor; int /*<<< orphan*/  destroyer; int /*<<< orphan*/  resend_timer; int /*<<< orphan*/  ack_timer; int /*<<< orphan*/  deadspan; int /*<<< orphan*/  lifetimer; int /*<<< orphan*/  acks_window; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RXRPC_CALL_CLIENT_SEND_REQUEST ; 
 scalar_t__ RXRPC_MAXACKS ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct rxrpc_call*) ; 
 struct rxrpc_call* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_ack_time_expired ; 
 int /*<<< orphan*/  rxrpc_call_jar ; 
 int /*<<< orphan*/  rxrpc_call_life_expired ; 
 int /*<<< orphan*/  rxrpc_dead_call_expired ; 
 int /*<<< orphan*/  rxrpc_debug_id ; 
 int /*<<< orphan*/  rxrpc_destroy_call ; 
 int /*<<< orphan*/  rxrpc_process_call ; 
 int /*<<< orphan*/  rxrpc_resend_time_expired ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rxrpc_call *rxrpc_alloc_call(gfp_t gfp)
{
	struct rxrpc_call *call;

	call = kmem_cache_zalloc(rxrpc_call_jar, gfp);
	if (!call)
		return NULL;

	call->acks_winsz = 16;
	call->acks_window = kmalloc(call->acks_winsz * sizeof(unsigned long),
				    gfp);
	if (!call->acks_window) {
		kmem_cache_free(rxrpc_call_jar, call);
		return NULL;
	}

	setup_timer(&call->lifetimer, &rxrpc_call_life_expired,
		    (unsigned long) call);
	setup_timer(&call->deadspan, &rxrpc_dead_call_expired,
		    (unsigned long) call);
	setup_timer(&call->ack_timer, &rxrpc_ack_time_expired,
		    (unsigned long) call);
	setup_timer(&call->resend_timer, &rxrpc_resend_time_expired,
		    (unsigned long) call);
	INIT_WORK(&call->destroyer, &rxrpc_destroy_call);
	INIT_WORK(&call->processor, &rxrpc_process_call);
	INIT_LIST_HEAD(&call->accept_link);
	skb_queue_head_init(&call->rx_queue);
	skb_queue_head_init(&call->rx_oos_queue);
	init_waitqueue_head(&call->tx_waitq);
	spin_lock_init(&call->lock);
	rwlock_init(&call->state_lock);
	atomic_set(&call->usage, 1);
	call->debug_id = atomic_inc_return(&rxrpc_debug_id);
	call->state = RXRPC_CALL_CLIENT_SEND_REQUEST;

	memset(&call->sock_node, 0xed, sizeof(call->sock_node));

	call->rx_data_expect = 1;
	call->rx_data_eaten = 0;
	call->rx_first_oos = 0;
	call->ackr_win_top = call->rx_data_eaten + 1 + RXRPC_MAXACKS;
	call->creation_jif = jiffies;
	return call;
}