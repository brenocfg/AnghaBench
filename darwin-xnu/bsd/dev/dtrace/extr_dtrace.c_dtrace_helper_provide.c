#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_7__ {scalar_t__ dofs_type; } ;
typedef  TYPE_1__ dof_sec_t ;
struct TYPE_8__ {scalar_t__ dofhp_dof; } ;
typedef  TYPE_2__ dof_helper_t ;
struct TYPE_9__ {int dofh_secnum; int dofh_secsize; scalar_t__ dofh_secoff; } ;
typedef  TYPE_3__ dof_hdr_t ;

/* Variables and functions */
 scalar_t__ DOF_SECT_PROVIDER ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  dtrace_helper_provide_one (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_meta_lock ; 

__attribute__((used)) static void
dtrace_helper_provide(dof_helper_t *dhp, proc_t *p)
{
	uintptr_t daddr = (uintptr_t)dhp->dofhp_dof;
	dof_hdr_t *dof = (dof_hdr_t *)daddr;
	uint32_t i;

	LCK_MTX_ASSERT(&dtrace_meta_lock, LCK_MTX_ASSERT_OWNED);

	for (i = 0; i < dof->dofh_secnum; i++) {
		dof_sec_t *sec = (dof_sec_t *)(uintptr_t)(daddr +
		    dof->dofh_secoff + i * dof->dofh_secsize);

		if (sec->dofs_type != DOF_SECT_PROVIDER)
			continue;

		dtrace_helper_provide_one(dhp, sec, p);
	}
}