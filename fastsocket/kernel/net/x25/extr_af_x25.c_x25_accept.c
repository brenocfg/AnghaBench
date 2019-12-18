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
struct socket {int /*<<< orphan*/  state; struct sock* sk; } ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_type; int /*<<< orphan*/  sk_ack_backlog; int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_rcvtimeo; } ;
struct sk_buff {struct sock* sk; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  SS_CONNECTED ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_graft (struct sock*,struct socket*) ; 
 int x25_wait_for_data (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x25_accept(struct socket *sock, struct socket *newsock, int flags)
{
	struct sock *sk = sock->sk;
	struct sock *newsk;
	struct sk_buff *skb;
	int rc = -EINVAL;

	if (!sk || sk->sk_state != TCP_LISTEN)
		goto out;

	rc = -EOPNOTSUPP;
	if (sk->sk_type != SOCK_SEQPACKET)
		goto out;

	lock_sock(sk);
	rc = x25_wait_for_data(sk, sk->sk_rcvtimeo);
	if (rc)
		goto out2;
	skb = skb_dequeue(&sk->sk_receive_queue);
	rc = -EINVAL;
	if (!skb->sk)
		goto out2;
	newsk		 = skb->sk;
	sock_graft(newsk, newsock);

	/* Now attach up the new socket */
	skb->sk = NULL;
	kfree_skb(skb);
	sk->sk_ack_backlog--;
	newsock->state = SS_CONNECTED;
	rc = 0;
out2:
	release_sock(sk);
out:
	return rc;
}