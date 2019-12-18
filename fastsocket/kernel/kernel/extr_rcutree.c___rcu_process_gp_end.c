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
struct rcu_node {scalar_t__ completed; } ;
struct rcu_data {scalar_t__ completed; int /*<<< orphan*/ * nxttail; } ;

/* Variables and functions */
 size_t RCU_DONE_TAIL ; 
 size_t RCU_NEXT_READY_TAIL ; 
 size_t RCU_NEXT_TAIL ; 
 size_t RCU_WAIT_TAIL ; 

__attribute__((used)) static void
__rcu_process_gp_end(struct rcu_state *rsp, struct rcu_node *rnp, struct rcu_data *rdp)
{
	/* Did another grace period end? */
	if (rdp->completed != rnp->completed) {

		/* Advance callbacks.  No harm if list empty. */
		rdp->nxttail[RCU_DONE_TAIL] = rdp->nxttail[RCU_WAIT_TAIL];
		rdp->nxttail[RCU_WAIT_TAIL] = rdp->nxttail[RCU_NEXT_READY_TAIL];
		rdp->nxttail[RCU_NEXT_READY_TAIL] = rdp->nxttail[RCU_NEXT_TAIL];

		/* Remember that we saw this grace-period completion. */
		rdp->completed = rnp->completed;
	}
}