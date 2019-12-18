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
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct pep_sock {int /*<<< orphan*/  hlist; struct sock* listener; int /*<<< orphan*/  ackq; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 struct sock* __sk_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __sock_put (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int pep_accept_conn (struct sock*,struct sk_buff*) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int pep_wait_connreq (struct sock*,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_acceptq_removed (struct sock*) ; 
 int /*<<< orphan*/  sk_add_node (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_del_node_init (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

__attribute__((used)) static struct sock *pep_sock_accept(struct sock *sk, int flags, int *errp)
{
	struct pep_sock *pn = pep_sk(sk);
	struct sock *newsk = NULL;
	struct sk_buff *oskb;
	int err;

	lock_sock(sk);
	err = pep_wait_connreq(sk, flags & O_NONBLOCK);
	if (err)
		goto out;

	newsk = __sk_head(&pn->ackq);

	oskb = skb_dequeue(&newsk->sk_receive_queue);
	err = pep_accept_conn(newsk, oskb);
	if (err) {
		skb_queue_head(&newsk->sk_receive_queue, oskb);
		newsk = NULL;
		goto out;
	}

	sock_hold(sk);
	pep_sk(newsk)->listener = sk;

	sock_hold(newsk);
	sk_del_node_init(newsk);
	sk_acceptq_removed(sk);
	sk_add_node(newsk, &pn->hlist);
	__sock_put(newsk);

out:
	release_sock(sk);
	*errp = err;
	return newsk;
}