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
struct TYPE_4__ {int /*<<< orphan*/  cpuset_mems_allowed; int /*<<< orphan*/  user_nodemask; } ;
struct TYPE_3__ {int preferred_node; } ;
struct mempolicy {int flags; TYPE_2__ w; TYPE_1__ v; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  enum mpol_rebind_step { ____Placeholder_mpol_rebind_step } mpol_rebind_step ;

/* Variables and functions */
 int MPOL_F_LOCAL ; 
 int MPOL_F_RELATIVE_NODES ; 
 int MPOL_F_STATIC_NODES ; 
 void* first_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpol_relative_nodemask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ node_isset (int,int /*<<< orphan*/  const) ; 
 int node_remap (int,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void mpol_rebind_preferred(struct mempolicy *pol,
				  const nodemask_t *nodes,
				  enum mpol_rebind_step step)
{
	nodemask_t tmp;

	if (pol->flags & MPOL_F_STATIC_NODES) {
		int node = first_node(pol->w.user_nodemask);

		if (node_isset(node, *nodes)) {
			pol->v.preferred_node = node;
			pol->flags &= ~MPOL_F_LOCAL;
		} else
			pol->flags |= MPOL_F_LOCAL;
	} else if (pol->flags & MPOL_F_RELATIVE_NODES) {
		mpol_relative_nodemask(&tmp, &pol->w.user_nodemask, nodes);
		pol->v.preferred_node = first_node(tmp);
	} else if (!(pol->flags & MPOL_F_LOCAL)) {
		pol->v.preferred_node = node_remap(pol->v.preferred_node,
						   pol->w.cpuset_mems_allowed,
						   *nodes);
		pol->w.cpuset_mems_allowed = *nodes;
	}
}