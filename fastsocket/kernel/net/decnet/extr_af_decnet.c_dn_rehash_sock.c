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
struct sock {int dummy; } ;
struct hlist_head {int dummy; } ;
struct TYPE_2__ {int sdn_flags; } ;
struct dn_scp {TYPE_1__ addr; scalar_t__ addrloc; } ;

/* Variables and functions */
 struct dn_scp* DN_SK (struct sock*) ; 
 int SDF_WILD ; 
 int /*<<< orphan*/  dn_hash_lock ; 
 struct hlist_head* listen_hash (TYPE_1__*) ; 
 int /*<<< orphan*/  sk_add_node (struct sock*,struct hlist_head*) ; 
 int /*<<< orphan*/  sk_del_node_init (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dn_rehash_sock(struct sock *sk)
{
	struct hlist_head *list;
	struct dn_scp *scp = DN_SK(sk);

	if (scp->addr.sdn_flags & SDF_WILD)
		return;

	write_lock_bh(&dn_hash_lock);
	sk_del_node_init(sk);
	DN_SK(sk)->addrloc = 0;
	list = listen_hash(&DN_SK(sk)->addr);
	sk_add_node(sk, list);
	write_unlock_bh(&dn_hash_lock);
}