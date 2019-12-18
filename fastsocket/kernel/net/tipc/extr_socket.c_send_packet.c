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
struct tipc_port {int /*<<< orphan*/  connected; int /*<<< orphan*/  congested; int /*<<< orphan*/  ref; } ;
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sockaddr_tipc {int dummy; } ;
struct sock {int /*<<< orphan*/ * sk_sleep; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_iovlen; scalar_t__ msg_name; } ;
struct kiocb {int dummy; } ;

/* Variables and functions */
 int ELINKCONG ; 
 int ENOTCONN ; 
 int EPIPE ; 
 int EWOULDBLOCK ; 
 int MSG_DONTWAIT ; 
 scalar_t__ SS_CONNECTED ; 
 scalar_t__ SS_DISCONNECTING ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int send_msg (struct kiocb*,struct socket*,struct msghdr*,size_t) ; 
 int tipc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_port* tipc_sk_port (struct sock*) ; 
 scalar_t__ unlikely (int) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int send_packet(struct kiocb *iocb, struct socket *sock,
		       struct msghdr *m, size_t total_len)
{
	struct sock *sk = sock->sk;
	struct tipc_port *tport = tipc_sk_port(sk);
	struct sockaddr_tipc *dest = (struct sockaddr_tipc *)m->msg_name;
	int res;

	/* Handle implied connection establishment */

	if (unlikely(dest))
		return send_msg(iocb, sock, m, total_len);

	if (iocb)
		lock_sock(sk);

	do {
		if (unlikely(sock->state != SS_CONNECTED)) {
			if (sock->state == SS_DISCONNECTING)
				res = -EPIPE;
			else
				res = -ENOTCONN;
			break;
		}

		res = tipc_send(tport->ref, m->msg_iovlen, m->msg_iov);
		if (likely(res != -ELINKCONG)) {
			break;
		}
		if (m->msg_flags & MSG_DONTWAIT) {
			res = -EWOULDBLOCK;
			break;
		}
		release_sock(sk);
		res = wait_event_interruptible(*sk->sk_sleep,
			(!tport->congested || !tport->connected));
		lock_sock(sk);
		if (res)
			break;
	} while (1);

	if (iocb)
		release_sock(sk);
	return res;
}