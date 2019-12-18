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
struct rcu_state {int dummy; } ;
struct rcu_node {int /*<<< orphan*/  lock; int /*<<< orphan*/  completed; } ;
struct rcu_data {scalar_t__ completed; struct rcu_node* mynode; } ;

/* Variables and functions */
 scalar_t__ ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __rcu_process_gp_end (struct rcu_state*,struct rcu_node*,struct rcu_data*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
rcu_process_gp_end(struct rcu_state *rsp, struct rcu_data *rdp)
{
	unsigned long flags;
	struct rcu_node *rnp;

	local_irq_save(flags);
	rnp = rdp->mynode;
	if (rdp->completed == ACCESS_ONCE(rnp->completed) || /* outside lock. */
	    !spin_trylock(&rnp->lock)) { /* irqs already off, retry later. */
		local_irq_restore(flags);
		return;
	}
	__rcu_process_gp_end(rsp, rnp, rdp);
	spin_unlock_irqrestore(&rnp->lock, flags);
}