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
struct socket {int state; struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_sleep; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int SHUT_RDWR ; 
#define  SS_CONNECTED 130 
#define  SS_CONNECTING 129 
#define  SS_DISCONNECTING 128 
 int /*<<< orphan*/  TIPC_CONN_SHUTDOWN ; 
 TYPE_1__* TIPC_SKB_CB (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  discard_rx_queue (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  msg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  tipc_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_queue_size ; 
 int /*<<< orphan*/  tipc_reject_msg (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_shutdown (int /*<<< orphan*/ ) ; 
 struct tipc_port* tipc_sk_port (struct sock*) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shutdown(struct socket *sock, int how)
{
	struct sock *sk = sock->sk;
	struct tipc_port *tport = tipc_sk_port(sk);
	struct sk_buff *buf;
	int res;

	if (how != SHUT_RDWR)
		return -EINVAL;

	lock_sock(sk);

	switch (sock->state) {
	case SS_CONNECTING:
	case SS_CONNECTED:

		/* Disconnect and send a 'FIN+' or 'FIN-' message to peer */
restart:
		buf = __skb_dequeue(&sk->sk_receive_queue);
		if (buf) {
			atomic_dec(&tipc_queue_size);
			if (TIPC_SKB_CB(buf)->handle != msg_data(buf_msg(buf))) {
				buf_discard(buf);
				goto restart;
			}
			tipc_disconnect(tport->ref);
			tipc_reject_msg(buf, TIPC_CONN_SHUTDOWN);
		} else {
			tipc_shutdown(tport->ref);
		}

		sock->state = SS_DISCONNECTING;

		/* fall through */

	case SS_DISCONNECTING:

		/* Discard any unreceived messages; wake up sleeping tasks */

		discard_rx_queue(sk);
		if (waitqueue_active(sk->sk_sleep))
			wake_up_interruptible(sk->sk_sleep);
		res = 0;
		break;

	default:
		res = -ENOTCONN;
	}

	release_sock(sk);
	return res;
}