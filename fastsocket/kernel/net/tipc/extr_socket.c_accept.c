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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct tipc_sock {TYPE_1__ peer_name; struct tipc_port* p; } ;
struct tipc_port {int /*<<< orphan*/  conn_instance; int /*<<< orphan*/  conn_type; int /*<<< orphan*/  ref; } ;
struct tipc_msg {int dummy; } ;
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/ * sk_sleep; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EWOULDBLOCK ; 
 int O_NONBLOCK ; 
 scalar_t__ SS_CONNECTED ; 
 scalar_t__ SS_LISTENING ; 
 scalar_t__ SS_READY ; 
 int /*<<< orphan*/  __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  advance_rx_queue (struct sock*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  msg_data_sz (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_dbg (struct tipc_msg*,char*) ; 
 int /*<<< orphan*/  msg_importance (struct tipc_msg*) ; 
 scalar_t__ msg_named (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_nameinst (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_nametype (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_orignode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_origport (struct tipc_msg*) ; 
 int /*<<< orphan*/  reject_rx_queue (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  send_packet (int /*<<< orphan*/ *,struct socket*,struct msghdr*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tipc_connect2port (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int tipc_create (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_set_portimportance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int accept(struct socket *sock, struct socket *new_sock, int flags)
{
	struct sock *sk = sock->sk;
	struct sk_buff *buf;
	int res;

	lock_sock(sk);

	if (sock->state == SS_READY) {
		res = -EOPNOTSUPP;
		goto exit;
	}
	if (sock->state != SS_LISTENING) {
		res = -EINVAL;
		goto exit;
	}

	while (skb_queue_empty(&sk->sk_receive_queue)) {
		if (flags & O_NONBLOCK) {
			res = -EWOULDBLOCK;
			goto exit;
		}
		release_sock(sk);
		res = wait_event_interruptible(*sk->sk_sleep,
				(!skb_queue_empty(&sk->sk_receive_queue)));
		lock_sock(sk);
		if (res)
			goto exit;
	}

	buf = skb_peek(&sk->sk_receive_queue);

	res = tipc_create(sock_net(sock->sk), new_sock, 0, 0);
	if (!res) {
		struct sock *new_sk = new_sock->sk;
		struct tipc_sock *new_tsock = tipc_sk(new_sk);
		struct tipc_port *new_tport = new_tsock->p;
		u32 new_ref = new_tport->ref;
		struct tipc_msg *msg = buf_msg(buf);

		lock_sock(new_sk);

		/*
		 * Reject any stray messages received by new socket
		 * before the socket lock was taken (very, very unlikely)
		 */

		reject_rx_queue(new_sk);

		/* Connect new socket to it's peer */

		new_tsock->peer_name.ref = msg_origport(msg);
		new_tsock->peer_name.node = msg_orignode(msg);
		tipc_connect2port(new_ref, &new_tsock->peer_name);
		new_sock->state = SS_CONNECTED;

		tipc_set_portimportance(new_ref, msg_importance(msg));
		if (msg_named(msg)) {
			new_tport->conn_type = msg_nametype(msg);
			new_tport->conn_instance = msg_nameinst(msg);
		}

		/*
		 * Respond to 'SYN-' by discarding it & returning 'ACK'-.
		 * Respond to 'SYN+' by queuing it on new socket.
		 */

		msg_dbg(msg,"<ACC<: ");
		if (!msg_data_sz(msg)) {
			struct msghdr m = {NULL,};

			advance_rx_queue(sk);
			send_packet(NULL, new_sock, &m, 0);
		} else {
			__skb_dequeue(&sk->sk_receive_queue);
			__skb_queue_head(&new_sk->sk_receive_queue, buf);
		}
		release_sock(new_sk);
	}
exit:
	release_sock(sk);
	return res;
}