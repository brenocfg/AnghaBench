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
typedef  scalar_t__ u32 ;
struct tipc_port {scalar_t__ conn_unacked; int /*<<< orphan*/  ref; } ;
struct tipc_msg {int dummy; } ;
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/ * sk_sleep; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int msg_iovlen; scalar_t__ msg_control; TYPE_1__* msg_iov; int /*<<< orphan*/  msg_flags; scalar_t__ msg_namelen; } ;
struct kiocb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int EWOULDBLOCK ; 
 int MSG_DONTWAIT ; 
 int MSG_PEEK ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 scalar_t__ SS_CONNECTING ; 
 scalar_t__ SS_DISCONNECTING ; 
 scalar_t__ SS_READY ; 
 scalar_t__ SS_UNCONNECTED ; 
 scalar_t__ TIPC_CONN_SHUTDOWN ; 
 scalar_t__ TIPC_FLOW_CONTROL_WIN ; 
 int /*<<< orphan*/  advance_rx_queue (struct sock*) ; 
 int anc_data_recv (struct msghdr*,struct tipc_msg*,struct tipc_port*) ; 
 int auto_connect (struct socket*,struct tipc_msg*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  msg_data (struct tipc_msg*) ; 
 unsigned int msg_data_sz (struct tipc_msg*) ; 
 scalar_t__ msg_errcode (struct tipc_msg*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  set_orig_addr (struct msghdr*,struct tipc_msg*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_acknowledge (int /*<<< orphan*/ ,scalar_t__) ; 
 struct tipc_port* tipc_sk_port (struct sock*) ; 
 scalar_t__ unlikely (int) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int recv_msg(struct kiocb *iocb, struct socket *sock,
		    struct msghdr *m, size_t buf_len, int flags)
{
	struct sock *sk = sock->sk;
	struct tipc_port *tport = tipc_sk_port(sk);
	struct sk_buff *buf;
	struct tipc_msg *msg;
	unsigned int sz;
	u32 err;
	int res;

	/* Catch invalid receive requests */

	if (m->msg_iovlen != 1)
		return -EOPNOTSUPP;   /* Don't do multiple iovec entries yet */

	if (unlikely(!buf_len))
		return -EINVAL;

	m->msg_namelen = 0;
	lock_sock(sk);

	if (unlikely(sock->state == SS_UNCONNECTED)) {
		res = -ENOTCONN;
		goto exit;
	}

restart:

	/* Look for a message in receive queue; wait if necessary */

	while (skb_queue_empty(&sk->sk_receive_queue)) {
		if (sock->state == SS_DISCONNECTING) {
			res = -ENOTCONN;
			goto exit;
		}
		if (flags & MSG_DONTWAIT) {
			res = -EWOULDBLOCK;
			goto exit;
		}
		release_sock(sk);
		res = wait_event_interruptible(*sk->sk_sleep,
			(!skb_queue_empty(&sk->sk_receive_queue) ||
			 (sock->state == SS_DISCONNECTING)));
		lock_sock(sk);
		if (res)
			goto exit;
	}

	/* Look at first message in receive queue */

	buf = skb_peek(&sk->sk_receive_queue);
	msg = buf_msg(buf);
	sz = msg_data_sz(msg);
	err = msg_errcode(msg);

	/* Complete connection setup for an implied connect */

	if (unlikely(sock->state == SS_CONNECTING)) {
		res = auto_connect(sock, msg);
		if (res)
			goto exit;
	}

	/* Discard an empty non-errored message & try again */

	if ((!sz) && (!err)) {
		advance_rx_queue(sk);
		goto restart;
	}

	/* Capture sender's address (optional) */

	set_orig_addr(m, msg);

	/* Capture ancillary data (optional) */

	res = anc_data_recv(m, msg, tport);
	if (res)
		goto exit;

	/* Capture message data (if valid) & compute return value (always) */

	if (!err) {
		if (unlikely(buf_len < sz)) {
			sz = buf_len;
			m->msg_flags |= MSG_TRUNC;
		}
		if (unlikely(copy_to_user(m->msg_iov->iov_base, msg_data(msg),
					  sz))) {
			res = -EFAULT;
			goto exit;
		}
		res = sz;
	} else {
		if ((sock->state == SS_READY) ||
		    ((err == TIPC_CONN_SHUTDOWN) || m->msg_control))
			res = 0;
		else
			res = -ECONNRESET;
	}

	/* Consume received message (optional) */

	if (likely(!(flags & MSG_PEEK))) {
		if ((sock->state != SS_READY) &&
		    (++tport->conn_unacked >= TIPC_FLOW_CONTROL_WIN))
			tipc_acknowledge(tport->ref, tport->conn_unacked);
		advance_rx_queue(sk);
	}
exit:
	release_sock(sk);
	return res;
}