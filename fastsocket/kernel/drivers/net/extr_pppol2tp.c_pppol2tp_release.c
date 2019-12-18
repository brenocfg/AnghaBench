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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int dummy; } ;
struct pppol2tp_session {int /*<<< orphan*/  reorder_q; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  PPPOX_DEAD ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct pppol2tp_session* pppol2tp_sock_to_session (struct sock*) ; 
 int /*<<< orphan*/  pppox_unbind_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static int pppol2tp_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct pppol2tp_session *session;
	int error;

	if (!sk)
		return 0;

	error = -EBADF;
	lock_sock(sk);
	if (sock_flag(sk, SOCK_DEAD) != 0)
		goto error;

	pppox_unbind_sock(sk);

	/* Signal the death of the socket. */
	sk->sk_state = PPPOX_DEAD;
	sock_orphan(sk);
	sock->sk = NULL;

	session = pppol2tp_sock_to_session(sk);

	/* Purge any queued data */
	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_write_queue);
	if (session != NULL) {
		struct sk_buff *skb;
		while ((skb = skb_dequeue(&session->reorder_q))) {
			kfree_skb(skb);
			sock_put(sk);
		}
		sock_put(sk);
	}

	release_sock(sk);

	/* This will delete the session context via
	 * pppol2tp_session_destruct() if the socket's refcnt drops to
	 * zero.
	 */
	sock_put(sk);

	return 0;

error:
	release_sock(sk);
	return error;
}