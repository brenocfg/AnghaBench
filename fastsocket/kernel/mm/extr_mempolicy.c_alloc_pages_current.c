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
struct page {int dummy; } ;
struct mempolicy {scalar_t__ mode; } ;
typedef  int gfp_t ;
struct TYPE_2__ {struct mempolicy* mempolicy; } ;

/* Variables and functions */
 scalar_t__ MPOL_INTERLEAVE ; 
 int __GFP_THISNODE ; 
 struct page* __alloc_pages_nodemask (int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* alloc_page_interleave (int,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 struct mempolicy default_policy ; 
 int /*<<< orphan*/  get_mems_allowed () ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  interleave_nodes (struct mempolicy*) ; 
 int /*<<< orphan*/  numa_node_id () ; 
 int /*<<< orphan*/  policy_nodemask (int,struct mempolicy*) ; 
 int /*<<< orphan*/  policy_zonelist (int,struct mempolicy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_mems_allowed () ; 

struct page *alloc_pages_current(gfp_t gfp, unsigned order)
{
	struct mempolicy *pol = current->mempolicy;
	struct page *page;

	if (!pol || in_interrupt() || (gfp & __GFP_THISNODE))
		pol = &default_policy;

	get_mems_allowed();
	/*
	 * No reference counting needed for current->mempolicy
	 * nor system default_policy
	 */
	if (pol->mode == MPOL_INTERLEAVE)
		page = alloc_page_interleave(gfp, order, interleave_nodes(pol));
	else
		page = __alloc_pages_nodemask(gfp, order,
	      			policy_zonelist(gfp, pol, numa_node_id()),
				policy_nodemask(gfp, pol));
	put_mems_allowed();
	return page;
}