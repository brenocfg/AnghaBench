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
struct sock {int /*<<< orphan*/  sk_prot; int /*<<< orphan*/  sk_nulls_node; } ;
struct inet_sock {scalar_t__ sport; scalar_t__ num; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_nulls_del (int /*<<< orphan*/ *) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 TYPE_1__ ping_table ; 
 int /*<<< orphan*/  pr_debug (char*,struct inet_sock*,scalar_t__) ; 
 scalar_t__ sk_hashed (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ping_v4_unhash(struct sock *sk)
{
	struct inet_sock *isk = inet_sk(sk);
	pr_debug("ping_v4_unhash(isk=%p,isk->num=%u)\n", isk, isk->num);
	if (sk_hashed(sk)) {
		write_lock_bh(&ping_table.lock);
		hlist_nulls_del(&sk->sk_nulls_node);
		sock_put(sk);
		isk->num = 0;
		isk->sport = 0;
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
		write_unlock_bh(&ping_table.lock);
	}
}