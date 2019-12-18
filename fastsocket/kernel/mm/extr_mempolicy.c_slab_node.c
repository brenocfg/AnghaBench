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
struct zonelist {int dummy; } ;
struct zone {int node; } ;
struct TYPE_3__ {int preferred_node; int /*<<< orphan*/  nodes; } ;
struct mempolicy {int flags; int mode; TYPE_1__ v; } ;
typedef  enum zone_type { ____Placeholder_zone_type } zone_type ;
struct TYPE_4__ {struct zonelist* node_zonelists; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  MPOL_BIND 130 
 int MPOL_F_LOCAL ; 
#define  MPOL_INTERLEAVE 129 
#define  MPOL_PREFERRED 128 
 TYPE_2__* NODE_DATA (int) ; 
 int /*<<< orphan*/  first_zones_zonelist (struct zonelist*,int,int /*<<< orphan*/ *,struct zone**) ; 
 int gfp_zone (int /*<<< orphan*/ ) ; 
 int interleave_nodes (struct mempolicy*) ; 
 int numa_node_id () ; 

unsigned slab_node(struct mempolicy *policy)
{
	if (!policy || policy->flags & MPOL_F_LOCAL)
		return numa_node_id();

	switch (policy->mode) {
	case MPOL_PREFERRED:
		/*
		 * handled MPOL_F_LOCAL above
		 */
		return policy->v.preferred_node;

	case MPOL_INTERLEAVE:
		return interleave_nodes(policy);

	case MPOL_BIND: {
		/*
		 * Follow bind policy behavior and start allocation at the
		 * first node.
		 */
		struct zonelist *zonelist;
		struct zone *zone;
		enum zone_type highest_zoneidx = gfp_zone(GFP_KERNEL);
		zonelist = &NODE_DATA(numa_node_id())->node_zonelists[0];
		(void)first_zones_zonelist(zonelist, highest_zoneidx,
							&policy->v.nodes,
							&zone);
		return zone->node;
	}

	default:
		BUG();
	}
}