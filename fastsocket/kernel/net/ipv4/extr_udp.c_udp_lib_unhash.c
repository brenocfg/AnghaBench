#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct udp_table {struct udp_hslot* hash; } ;
struct udp_hslot {int /*<<< orphan*/  lock; } ;
struct sock {TYPE_2__* sk_prot; int /*<<< orphan*/  sk_hash; } ;
struct TYPE_6__ {scalar_t__ num; } ;
struct TYPE_4__ {struct udp_table* udp_table; } ;
struct TYPE_5__ {TYPE_1__ h; } ;

/* Variables and functions */
 TYPE_3__* inet_sk (struct sock*) ; 
 scalar_t__ sk_hashed (struct sock*) ; 
 scalar_t__ sk_nulls_del_node_init_rcu (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned int udp_hashfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void udp_lib_unhash(struct sock *sk)
{
	if (sk_hashed(sk)) {
		struct udp_table *udptable = sk->sk_prot->h.udp_table;
		unsigned int hash = udp_hashfn(sock_net(sk), sk->sk_hash);
		struct udp_hslot *hslot = &udptable->hash[hash];

		spin_lock_bh(&hslot->lock);
		if (sk_nulls_del_node_init_rcu(sk)) {
			inet_sk(sk)->num = 0;
			sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
		}
		spin_unlock_bh(&hslot->lock);
	}
}