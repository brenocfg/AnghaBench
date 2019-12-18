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
struct net {int /*<<< orphan*/  rules_mod_lock; } ;
struct fib_rules_ops {int /*<<< orphan*/  list; struct net* fro_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib_rules_cleanup_ops (struct fib_rules_ops*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_net (struct net*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void fib_rules_unregister(struct fib_rules_ops *ops)
{
	struct net *net = ops->fro_net;

	spin_lock(&net->rules_mod_lock);
	list_del_rcu(&ops->list);
	fib_rules_cleanup_ops(ops);
	spin_unlock(&net->rules_mod_lock);

	synchronize_rcu();
	release_net(net);
}