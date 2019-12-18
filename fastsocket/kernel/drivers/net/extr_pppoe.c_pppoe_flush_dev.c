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
struct sock {int sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct pppox_sock {struct net_device* pppoe_dev; struct pppox_sock* next; } ;
struct pppoe_net {int /*<<< orphan*/  hash_lock; struct pppox_sock** hash_table; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int PPPOE_HASH_SIZE ; 
 int PPPOX_BOUND ; 
 int PPPOX_CONNECTED ; 
 int PPPOX_ZOMBIE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct pppoe_net* pppoe_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pppox_unbind_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct sock* sk_pppox (struct pppox_sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pppoe_flush_dev(struct net_device *dev)
{
	struct pppoe_net *pn;
	int i;

	BUG_ON(dev == NULL);

	pn = pppoe_pernet(dev_net(dev));
	if (!pn) /* already freed */
		return;

	write_lock_bh(&pn->hash_lock);
	for (i = 0; i < PPPOE_HASH_SIZE; i++) {
		struct pppox_sock *po = pn->hash_table[i];
		struct sock *sk;

		while (po) {
			while (po && po->pppoe_dev != dev) {
				po = po->next;
			}

			if (!po)
				break;

			sk = sk_pppox(po);

			/* We always grab the socket lock, followed by the
			 * hash_lock, in that order.  Since we should hold the
			 * sock lock while doing any unbinding, we need to
			 * release the lock we're holding.  Hold a reference to
			 * the sock so it doesn't disappear as we're jumping
			 * between locks.
			 */

			sock_hold(sk);
			write_unlock_bh(&pn->hash_lock);
			lock_sock(sk);

			if (po->pppoe_dev == dev
			    && sk->sk_state & (PPPOX_CONNECTED | PPPOX_BOUND)) {
				pppox_unbind_sock(sk);
				sk->sk_state = PPPOX_ZOMBIE;
				sk->sk_state_change(sk);
				po->pppoe_dev = NULL;
				dev_put(dev);
			}

			release_sock(sk);
			sock_put(sk);

			/* Restart the process from the start of the current
			 * hash chain. We dropped locks so the world may have
			 * change from underneath us.
			 */

			BUG_ON(pppoe_pernet(dev_net(dev)) == NULL);
			write_lock_bh(&pn->hash_lock);
			po = pn->hash_table[i];
		}
	}
	write_unlock_bh(&pn->hash_lock);
}