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
struct zonelist {int dummy; } ;
struct TYPE_2__ {int preferred_node; int /*<<< orphan*/  nodes; } ;
struct mempolicy {int mode; int flags; TYPE_1__ v; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  MPOL_BIND 130 
 int MPOL_F_LOCAL ; 
#define  MPOL_INTERLEAVE 129 
#define  MPOL_PREFERRED 128 
 int __GFP_THISNODE ; 
 int first_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_isset (int,int /*<<< orphan*/ ) ; 
 struct zonelist* node_zonelist (int,int) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static struct zonelist *policy_zonelist(gfp_t gfp, struct mempolicy *policy,
	int nd)
{
	switch (policy->mode) {
	case MPOL_PREFERRED:
		if (!(policy->flags & MPOL_F_LOCAL))
			nd = policy->v.preferred_node;
		break;
	case MPOL_BIND:
		/*
		 * Normally, MPOL_BIND allocations are node-local within the
		 * allowed nodemask.  However, if __GFP_THISNODE is set and the
		 * current node is part of the mask, we use the zonelist for
		 * the first node in the mask instead.
		 */
		if (unlikely(gfp & __GFP_THISNODE) &&
				unlikely(!node_isset(nd, policy->v.nodes)))
			nd = first_node(policy->v.nodes);
		break;
	case MPOL_INTERLEAVE: /* should not happen */
		break;
	default:
		BUG();
	}
	return node_zonelist(nd, gfp);
}