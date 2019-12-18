#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nodemask_scratch {int /*<<< orphan*/  mask2; int /*<<< orphan*/  mask1; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpuset_mems_allowed; int /*<<< orphan*/  user_nodemask; } ;
struct mempolicy {size_t mode; int flags; TYPE_1__ w; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
struct TYPE_4__ {int (* create ) (struct mempolicy*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int MPOL_F_RELATIVE_NODES ; 
 size_t MPOL_PREFERRED ; 
 size_t N_HIGH_MEMORY ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  const cpuset_current_mems_allowed ; 
 TYPE_2__* mpol_ops ; 
 int /*<<< orphan*/  mpol_relative_nodemask (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ mpol_store_user_nodemask (struct mempolicy*) ; 
 int /*<<< orphan*/ * node_states ; 
 int /*<<< orphan*/  nodes_and (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 scalar_t__ nodes_empty (int /*<<< orphan*/  const) ; 
 int stub1 (struct mempolicy*,int /*<<< orphan*/ *) ; 
 int stub2 (struct mempolicy*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpol_set_nodemask(struct mempolicy *pol,
		     const nodemask_t *nodes, struct nodemask_scratch *nsc)
{
	int ret;

	/* if mode is MPOL_DEFAULT, pol is NULL. This is right. */
	if (pol == NULL)
		return 0;
	/* Check N_HIGH_MEMORY */
	nodes_and(nsc->mask1,
		  cpuset_current_mems_allowed, node_states[N_HIGH_MEMORY]);

	VM_BUG_ON(!nodes);
	if (pol->mode == MPOL_PREFERRED && nodes_empty(*nodes))
		nodes = NULL;	/* explicit local allocation */
	else {
		if (pol->flags & MPOL_F_RELATIVE_NODES)
			mpol_relative_nodemask(&nsc->mask2, nodes,&nsc->mask1);
		else
			nodes_and(nsc->mask2, *nodes, nsc->mask1);

		if (mpol_store_user_nodemask(pol))
			pol->w.user_nodemask = *nodes;
		else
			pol->w.cpuset_mems_allowed =
						cpuset_current_mems_allowed;
	}

	if (nodes)
		ret = mpol_ops[pol->mode].create(pol, &nsc->mask2);
	else
		ret = mpol_ops[pol->mode].create(pol, NULL);
	return ret;
}