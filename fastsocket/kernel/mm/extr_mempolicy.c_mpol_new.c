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
struct mempolicy {unsigned short mode; unsigned short flags; int /*<<< orphan*/  refcnt; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct mempolicy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned short MPOL_DEFAULT ; 
 unsigned short MPOL_F_RELATIVE_NODES ; 
 unsigned short MPOL_F_STATIC_NODES ; 
 unsigned short MPOL_PREFERRED ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct mempolicy* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* nodes_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ nodes_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_cache ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned short,unsigned short,int) ; 

__attribute__((used)) static struct mempolicy *mpol_new(unsigned short mode, unsigned short flags,
				  nodemask_t *nodes)
{
	struct mempolicy *policy;

	pr_debug("setting mode %d flags %d nodes[0] %lx\n",
		 mode, flags, nodes ? nodes_addr(*nodes)[0] : -1);

	if (mode == MPOL_DEFAULT) {
		if (nodes && !nodes_empty(*nodes))
			return ERR_PTR(-EINVAL);
		return NULL;	/* simply delete any existing policy */
	}
	VM_BUG_ON(!nodes);

	/*
	 * MPOL_PREFERRED cannot be used with MPOL_F_STATIC_NODES or
	 * MPOL_F_RELATIVE_NODES if the nodemask is empty (local allocation).
	 * All other modes require a valid pointer to a non-empty nodemask.
	 */
	if (mode == MPOL_PREFERRED) {
		if (nodes_empty(*nodes)) {
			if (((flags & MPOL_F_STATIC_NODES) ||
			     (flags & MPOL_F_RELATIVE_NODES)))
				return ERR_PTR(-EINVAL);
		}
	} else if (nodes_empty(*nodes))
		return ERR_PTR(-EINVAL);
	policy = kmem_cache_alloc(policy_cache, GFP_KERNEL);
	if (!policy)
		return ERR_PTR(-ENOMEM);
	atomic_set(&policy->refcnt, 1);
	policy->mode = mode;
	policy->flags = flags;

	return policy;
}