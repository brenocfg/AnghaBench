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
struct zonelist {int dummy; } ;
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct mempolicy {scalar_t__ mode; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ MPOL_INTERLEAVE ; 
 scalar_t__ PAGE_SHIFT ; 
 struct page* __alloc_pages_nodemask (int /*<<< orphan*/ ,int,struct zonelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mpol_put (struct mempolicy*) ; 
 struct page* alloc_page_interleave (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_mems_allowed () ; 
 struct mempolicy* get_vma_policy (int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long) ; 
 unsigned int interleave_nid (struct mempolicy*,struct vm_area_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  mpol_cond_put (struct mempolicy*) ; 
 int mpol_needs_cond_ref (struct mempolicy*) ; 
 int /*<<< orphan*/  policy_nodemask (int /*<<< orphan*/ ,struct mempolicy*) ; 
 struct zonelist* policy_zonelist (int /*<<< orphan*/ ,struct mempolicy*,int) ; 
 int /*<<< orphan*/  put_mems_allowed () ; 
 scalar_t__ unlikely (int) ; 

struct page *
alloc_pages_vma(gfp_t gfp, int order, struct vm_area_struct *vma,
		unsigned long addr, int node)
{
	struct mempolicy *pol = get_vma_policy(current, vma, addr);
	struct zonelist *zl;
	struct page *page;

	get_mems_allowed();
	if (unlikely(pol->mode == MPOL_INTERLEAVE)) {
		unsigned nid;

		nid = interleave_nid(pol, vma, addr, PAGE_SHIFT + order);
		mpol_cond_put(pol);
		page = alloc_page_interleave(gfp, order, nid);
		put_mems_allowed();
		return page;
	}
	zl = policy_zonelist(gfp, pol, node);
	if (unlikely(mpol_needs_cond_ref(pol))) {
		/*
		 * slow path: ref counted shared policy
		 */
		struct page *page =  __alloc_pages_nodemask(gfp, order,
						zl, policy_nodemask(gfp, pol));
		__mpol_put(pol);
		put_mems_allowed();
		return page;
	}
	/*
	 * fast path:  default or task policy
	 */
	page = __alloc_pages_nodemask(gfp, order, zl,
				      policy_nodemask(gfp, pol));
	put_mems_allowed();
	return page;
}