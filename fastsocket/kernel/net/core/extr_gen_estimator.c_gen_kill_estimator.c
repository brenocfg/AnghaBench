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
struct gnet_stats_rate_est {int dummy; } ;
struct gnet_stats_basic_packed {int dummy; } ;
struct gen_estimator {int /*<<< orphan*/  e_rcu; int /*<<< orphan*/  list; int /*<<< orphan*/ * bstats; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gen_kill_estimator ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  est_lock ; 
 int /*<<< orphan*/  est_root ; 
 struct gen_estimator* gen_find_node (struct gnet_stats_basic_packed*,struct gnet_stats_rate_est*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void gen_kill_estimator(struct gnet_stats_basic_packed *bstats,
			struct gnet_stats_rate_est *rate_est)
{
	struct gen_estimator *e;

	while ((e = gen_find_node(bstats, rate_est))) {
		rb_erase(&e->node, &est_root);

		write_lock_bh(&est_lock);
		e->bstats = NULL;
		write_unlock_bh(&est_lock);

		list_del_rcu(&e->list);
		call_rcu(&e->e_rcu, __gen_kill_estimator);
	}
}