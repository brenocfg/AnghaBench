#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* p_dtrace_lazy_dofs; int /*<<< orphan*/ * p_dtrace_helpers; } ;
typedef  TYPE_1__ proc_t ;
struct TYPE_8__ {int /*<<< orphan*/  dofiod_count; } ;
typedef  TYPE_2__ dof_ioctl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DOF_IOCTL_DATA_T_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_dof_mode_lock ; 
 int /*<<< orphan*/  dtrace_sprlock (TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_sprunlock (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_unlock_shared (int /*<<< orphan*/ *) ; 

void
dtrace_lazy_dofs_destroy(proc_t *p)
{
	lck_rw_lock_shared(&dtrace_dof_mode_lock);
	dtrace_sprlock(p);
	
	ASSERT(p->p_dtrace_lazy_dofs == NULL || p->p_dtrace_helpers == NULL);

	dof_ioctl_data_t* lazy_dofs = p->p_dtrace_lazy_dofs;
	p->p_dtrace_lazy_dofs = NULL;

	dtrace_sprunlock(p);
	lck_rw_unlock_shared(&dtrace_dof_mode_lock);

	if (lazy_dofs) {
		kmem_free(lazy_dofs, DOF_IOCTL_DATA_T_SIZE(lazy_dofs->dofiod_count));
	}
}