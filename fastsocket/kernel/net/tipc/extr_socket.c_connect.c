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
struct tipc_msg {int dummy; } ;
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sockaddr_tipc {scalar_t__ addrtype; } ;
struct sockaddr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_rcvtimeo; int /*<<< orphan*/ * sk_sleep; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int msg_namelen; struct sockaddr* msg_name; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int EALREADY ; 
 int ECONNREFUSED ; 
 int EINVAL ; 
 int EISCONN ; 
 int EOPNOTSUPP ; 
 int ETIMEDOUT ; 
 int EWOULDBLOCK ; 
 int O_NONBLOCK ; 
 scalar_t__ SS_CONNECTED ; 
 scalar_t__ SS_CONNECTING ; 
 scalar_t__ SS_DISCONNECTING ; 
 scalar_t__ SS_LISTENING ; 
 scalar_t__ SS_READY ; 
 scalar_t__ SS_UNCONNECTED ; 
 scalar_t__ TIPC_ADDR_MCAST ; 
 int /*<<< orphan*/  advance_rx_queue (struct sock*) ; 
 int auto_connect (struct socket*,struct tipc_msg*) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  msg_data_sz (struct tipc_msg*) ; 
 int /*<<< orphan*/  reject_rx_queue (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int send_msg (int /*<<< orphan*/ *,struct socket*,struct msghdr*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int connect(struct socket *sock, struct sockaddr *dest, int destlen,
		   int flags)
{
	struct sock *sk = sock->sk;
	struct sockaddr_tipc *dst = (struct sockaddr_tipc *)dest;
	struct msghdr m = {NULL,};
	struct sk_buff *buf;
	struct tipc_msg *msg;
	int res;

	lock_sock(sk);

	/* For now, TIPC does not allow use of connect() with DGRAM/RDM types */

	if (sock->state == SS_READY) {
		res = -EOPNOTSUPP;
		goto exit;
	}

	/* For now, TIPC does not support the non-blocking form of connect() */

	if (flags & O_NONBLOCK) {
		res = -EWOULDBLOCK;
		goto exit;
	}

	/* Issue Posix-compliant error code if socket is in the wrong state */

	if (sock->state == SS_LISTENING) {
		res = -EOPNOTSUPP;
		goto exit;
	}
	if (sock->state == SS_CONNECTING) {
		res = -EALREADY;
		goto exit;
	}
	if (sock->state != SS_UNCONNECTED) {
		res = -EISCONN;
		goto exit;
	}

	/*
	 * Reject connection attempt using multicast address
	 *
	 * Note: send_msg() validates the rest of the address fields,
	 *       so there's no need to do it here
	 */

	if (dst->addrtype == TIPC_ADDR_MCAST) {
		res = -EINVAL;
		goto exit;
	}

	/* Reject any messages already in receive queue (very unlikely) */

	reject_rx_queue(sk);

	/* Send a 'SYN-' to destination */

	m.msg_name = dest;
	m.msg_namelen = destlen;
	res = send_msg(NULL, sock, &m, 0);
	if (res < 0) {
		goto exit;
	}

	/* Wait until an 'ACK' or 'RST' arrives, or a timeout occurs */

	release_sock(sk);
	res = wait_event_interruptible_timeout(*sk->sk_sleep,
			(!skb_queue_empty(&sk->sk_receive_queue) ||
			(sock->state != SS_CONNECTING)),
			sk->sk_rcvtimeo);
	lock_sock(sk);

	if (res > 0) {
		buf = skb_peek(&sk->sk_receive_queue);
		if (buf != NULL) {
			msg = buf_msg(buf);
			res = auto_connect(sock, msg);
			if (!res) {
				if (!msg_data_sz(msg))
					advance_rx_queue(sk);
			}
		} else {
			if (sock->state == SS_CONNECTED) {
				res = -EISCONN;
			} else {
				res = -ECONNREFUSED;
			}
		}
	} else {
		if (res == 0)
			res = -ETIMEDOUT;
		else
			; /* leave "res" unchanged */
		sock->state = SS_DISCONNECTING;
	}

exit:
	release_sock(sk);
	return res;
}