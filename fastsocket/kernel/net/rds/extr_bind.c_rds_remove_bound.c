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
struct rds_sock {scalar_t__ rs_bound_addr; int /*<<< orphan*/  rs_bound_node; int /*<<< orphan*/  rs_bound_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_bind_lock ; 
 int /*<<< orphan*/  rds_sock_put (struct rds_sock*) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_sock*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rds_remove_bound(struct rds_sock *rs)
{
	unsigned long flags;

	spin_lock_irqsave(&rds_bind_lock, flags);

	if (rs->rs_bound_addr) {
		rdsdebug("rs %p unbinding from %pI4:%d\n",
		  rs, &rs->rs_bound_addr,
		  ntohs(rs->rs_bound_port));

		hlist_del_init_rcu(&rs->rs_bound_node);
		rds_sock_put(rs);
		rs->rs_bound_addr = 0;
	}

	spin_unlock_irqrestore(&rds_bind_lock, flags);
}