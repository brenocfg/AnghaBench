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
struct sock {int dummy; } ;
struct netlink_sock {scalar_t__ pid; int ngroups; int flags; int /*<<< orphan*/  groups; } ;
struct netlink_broadcast_data {scalar_t__ pid; int group; int failure; int delivery_failure; int congested; int delivered; int /*<<< orphan*/ * skb2; int /*<<< orphan*/  skb; int /*<<< orphan*/  allocation; int /*<<< orphan*/  net; struct sock* exclude_sk; } ;

/* Variables and functions */
 int NETLINK_BROADCAST_SEND_ERROR ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int netlink_broadcast_deliver (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlink_overrun (struct sock*) ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 scalar_t__ sk_filter (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_clone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_orphan (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int do_one_broadcast(struct sock *sk,
				   struct netlink_broadcast_data *p)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	int val;

	if (p->exclude_sk == sk)
		goto out;

	if (nlk->pid == p->pid || p->group - 1 >= nlk->ngroups ||
	    !test_bit(p->group - 1, nlk->groups))
		goto out;

	if (!net_eq(sock_net(sk), p->net))
		goto out;

	if (p->failure) {
		netlink_overrun(sk);
		goto out;
	}

	sock_hold(sk);
	if (p->skb2 == NULL) {
		if (skb_shared(p->skb)) {
			p->skb2 = skb_clone(p->skb, p->allocation);
		} else {
			p->skb2 = skb_get(p->skb);
			/*
			 * skb ownership may have been set when
			 * delivered to a previous socket.
			 */
			skb_orphan(p->skb2);
		}
	}
	if (p->skb2 == NULL) {
		netlink_overrun(sk);
		/* Clone failed. Notify ALL listeners. */
		p->failure = 1;
		if (nlk->flags & NETLINK_BROADCAST_SEND_ERROR)
			p->delivery_failure = 1;
	} else if (sk_filter(sk, p->skb2)) {
		kfree_skb(p->skb2);
		p->skb2 = NULL;
	} else if ((val = netlink_broadcast_deliver(sk, p->skb2)) < 0) {
		netlink_overrun(sk);
		if (nlk->flags & NETLINK_BROADCAST_SEND_ERROR)
			p->delivery_failure = 1;
	} else {
		p->congested |= val;
		p->delivered = 1;
		p->skb2 = NULL;
	}
	sock_put(sk);

out:
	return 0;
}