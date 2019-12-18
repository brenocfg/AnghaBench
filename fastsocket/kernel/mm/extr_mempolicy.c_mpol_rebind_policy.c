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
struct TYPE_3__ {int /*<<< orphan*/  cpuset_mems_allowed; } ;
struct mempolicy {int flags; size_t mode; TYPE_1__ w; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  enum mpol_rebind_step { ____Placeholder_mpol_rebind_step } mpol_rebind_step ;
struct TYPE_4__ {int /*<<< orphan*/  (* rebind ) (struct mempolicy*,int /*<<< orphan*/  const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int MPOL_F_REBINDING ; 
 int MPOL_REBIND_NSTEP ; 
 int MPOL_REBIND_STEP1 ; 
 int MPOL_REBIND_STEP2 ; 
 TYPE_2__* mpol_ops ; 
 int /*<<< orphan*/  mpol_store_user_nodemask (struct mempolicy*) ; 
 scalar_t__ nodes_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub1 (struct mempolicy*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void mpol_rebind_policy(struct mempolicy *pol, const nodemask_t *newmask,
				enum mpol_rebind_step step)
{
	if (!pol)
		return;
	if (!mpol_store_user_nodemask(pol) && step == 0 &&
	    nodes_equal(pol->w.cpuset_mems_allowed, *newmask))
		return;

	if (step == MPOL_REBIND_STEP1 && (pol->flags & MPOL_F_REBINDING))
		return;

	if (step == MPOL_REBIND_STEP2 && !(pol->flags & MPOL_F_REBINDING))
		BUG();

	if (step == MPOL_REBIND_STEP1)
		pol->flags |= MPOL_F_REBINDING;
	else if (step == MPOL_REBIND_STEP2)
		pol->flags &= ~MPOL_F_REBINDING;
	else if (step >= MPOL_REBIND_NSTEP)
		BUG();

	mpol_ops[pol->mode].rebind(pol, newmask, step);
}