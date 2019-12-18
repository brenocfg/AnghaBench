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
struct tipc_port {int /*<<< orphan*/  ref; } ;
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ handle; } ;

/* Variables and functions */
 scalar_t__ SS_CONNECTED ; 
 scalar_t__ SS_CONNECTING ; 
 scalar_t__ SS_DISCONNECTING ; 
 int /*<<< orphan*/  TIPC_ERR_NO_PORT ; 
 TYPE_1__* TIPC_SKB_CB (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  discard_rx_queue (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 scalar_t__ msg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int tipc_deleteport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_queue_size ; 
 int /*<<< orphan*/  tipc_reject_msg (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct tipc_port* tipc_sk_port (struct sock*) ; 
 int /*<<< orphan*/  tipc_user_count ; 

__attribute__((used)) static int release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct tipc_port *tport;
	struct sk_buff *buf;
	int res;

	/*
	 * Exit if socket isn't fully initialized (occurs when a failed accept()
	 * releases a pre-allocated child socket that was never used)
	 */

	if (sk == NULL)
		return 0;

	tport = tipc_sk_port(sk);
	lock_sock(sk);

	/*
	 * Reject all unreceived messages, except on an active connection
	 * (which disconnects locally & sends a 'FIN+' to peer)
	 */

	while (sock->state != SS_DISCONNECTING) {
		buf = __skb_dequeue(&sk->sk_receive_queue);
		if (buf == NULL)
			break;
		atomic_dec(&tipc_queue_size);
		if (TIPC_SKB_CB(buf)->handle != msg_data(buf_msg(buf)))
			buf_discard(buf);
		else {
			if ((sock->state == SS_CONNECTING) ||
			    (sock->state == SS_CONNECTED)) {
				sock->state = SS_DISCONNECTING;
				tipc_disconnect(tport->ref);
			}
			tipc_reject_msg(buf, TIPC_ERR_NO_PORT);
		}
	}

	/*
	 * Delete TIPC port; this ensures no more messages are queued
	 * (also disconnects an active connection & sends a 'FIN-' to peer)
	 */

	res = tipc_deleteport(tport->ref);

	/* Discard any remaining (connection-based) messages in receive queue */

	discard_rx_queue(sk);

	/* Reject any messages that accumulated in backlog queue */

	sock->state = SS_DISCONNECTING;
	release_sock(sk);

	sock_put(sk);
	sock->sk = NULL;

	atomic_dec(&tipc_user_count);
	return res;
}