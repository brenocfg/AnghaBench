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
struct TYPE_2__ {int /*<<< orphan*/  nodes; } ;
struct mempolicy {scalar_t__ mode; TYPE_1__ v; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ MPOL_BIND ; 
 scalar_t__ cpuset_nodemask_valid_mems_allowed (int /*<<< orphan*/ *) ; 
 scalar_t__ gfp_zone (int /*<<< orphan*/ ) ; 
 scalar_t__ policy_zone ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static nodemask_t *policy_nodemask(gfp_t gfp, struct mempolicy *policy)
{
	/* Lower zones don't get a nodemask applied for MPOL_BIND */
	if (unlikely(policy->mode == MPOL_BIND) &&
			gfp_zone(gfp) >= policy_zone &&
			cpuset_nodemask_valid_mems_allowed(&policy->v.nodes))
		return &policy->v.nodes;

	return NULL;
}