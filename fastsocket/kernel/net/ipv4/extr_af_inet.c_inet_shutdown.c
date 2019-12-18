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
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sock {int sk_state; int sk_shutdown; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;TYPE_1__* sk_prot; } ;
struct TYPE_2__ {int (* disconnect ) (struct sock*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* shutdown ) (struct sock*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int RCV_SHUTDOWN ; 
 int SHUTDOWN_MASK ; 
 scalar_t__ SS_CONNECTED ; 
 scalar_t__ SS_CONNECTING ; 
 void* SS_DISCONNECTING ; 
 void* SS_UNCONNECTED ; 
 int TCPF_CLOSE ; 
 int TCPF_SYN_RECV ; 
 int TCPF_SYN_SENT ; 
#define  TCP_CLOSE 130 
#define  TCP_LISTEN 129 
#define  TCP_SYN_SENT 128 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int) ; 
 int stub2 (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct sock*) ; 

int inet_shutdown(struct socket *sock, int how)
{
	struct sock *sk = sock->sk;
	int err = 0;

	/* This should really check to make sure
	 * the socket is a TCP socket. (WHY AC...)
	 */
	how++; /* maps 0->1 has the advantage of making bit 1 rcvs and
		       1->2 bit 2 snds.
		       2->3 */
	if ((how & ~SHUTDOWN_MASK) || !how)	/* MAXINT->0 */
		return -EINVAL;

	lock_sock(sk);
	if (sock->state == SS_CONNECTING) {
		if ((1 << sk->sk_state) &
		    (TCPF_SYN_SENT | TCPF_SYN_RECV | TCPF_CLOSE))
			sock->state = SS_DISCONNECTING;
		else
			sock->state = SS_CONNECTED;
	}

	switch (sk->sk_state) {
	case TCP_CLOSE:
		err = -ENOTCONN;
		/* Hack to wake up other listeners, who can poll for
		   POLLHUP, even on eg. unconnected UDP sockets -- RR */
	default:
		sk->sk_shutdown |= how;
		if (sk->sk_prot->shutdown)
			sk->sk_prot->shutdown(sk, how);
		break;

	/* Remaining two branches are temporary solution for missing
	 * close() in multithreaded environment. It is _not_ a good idea,
	 * but we have no choice until close() is repaired at VFS level.
	 */
	case TCP_LISTEN:
		if (!(how & RCV_SHUTDOWN))
			break;
		/* Fall through */
	case TCP_SYN_SENT:
		err = sk->sk_prot->disconnect(sk, O_NONBLOCK);
		sock->state = err ? SS_DISCONNECTING : SS_UNCONNECTED;
		break;
	}

	/* Wake up anyone sleeping in poll. */
	sk->sk_state_change(sk);
	release_sock(sk);
	return err;
}