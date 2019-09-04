#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* p_dtrace_lazy_dofs; int /*<<< orphan*/ * p_dtrace_helpers; int /*<<< orphan*/  p_dtrace_sprlock; } ;
typedef  TYPE_1__ proc_t ;
struct TYPE_12__ {int /*<<< orphan*/  dofiod_count; } ;
typedef  TYPE_2__ dof_ioctl_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t DOF_IOCTL_DATA_T_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ DTRACE_DOF_MODE_LAZY_OFF ; 
 int DTRACE_LAZY_DOFS_DUPLICATED ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int /*<<< orphan*/  bcopy (TYPE_2__*,TYPE_2__*,size_t) ; 
 scalar_t__ dtrace_dof_mode ; 
 int /*<<< orphan*/  dtrace_dof_mode_lock ; 
 int /*<<< orphan*/  dtrace_lazy_dofs_process (TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_sprlock (TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_sprunlock (TYPE_1__*) ; 
 TYPE_2__* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_unlock_shared (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_lazy_dofs_duplicate(proc_t *parent, proc_t *child)
{
	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_NOTOWNED);
	LCK_MTX_ASSERT(&parent->p_dtrace_sprlock, LCK_MTX_ASSERT_NOTOWNED);
	LCK_MTX_ASSERT(&child->p_dtrace_sprlock, LCK_MTX_ASSERT_NOTOWNED);

	lck_rw_lock_shared(&dtrace_dof_mode_lock);
	dtrace_sprlock(parent);

	/*
	 * We need to make sure that the transition to lazy dofs -> helpers
	 * was atomic for our parent
	 */
	ASSERT(parent->p_dtrace_lazy_dofs == NULL || parent->p_dtrace_helpers == NULL);
	/*
	 * In theory we should hold the child sprlock, but this is safe...
	 */
	ASSERT(child->p_dtrace_lazy_dofs == NULL && child->p_dtrace_helpers == NULL);

	dof_ioctl_data_t* parent_dofs = parent->p_dtrace_lazy_dofs;
	dof_ioctl_data_t* child_dofs = NULL;
	if (parent_dofs) {
		size_t parent_dofs_size = DOF_IOCTL_DATA_T_SIZE(parent_dofs->dofiod_count);
		child_dofs = kmem_alloc(parent_dofs_size, KM_SLEEP);
		bcopy(parent_dofs, child_dofs, parent_dofs_size);
	}

	dtrace_sprunlock(parent);

	if (child_dofs) {
		dtrace_sprlock(child);
		child->p_dtrace_lazy_dofs = child_dofs;
		dtrace_sprunlock(child);
		/**
		 * We process the DOF at this point if the mode is set to
		 * LAZY_OFF. This can happen if DTrace is still processing the
		 * DOF of other process (which can happen because the
		 * protected pager can have a huge latency)
		 * but has not processed our parent yet
		 */
		if (dtrace_dof_mode == DTRACE_DOF_MODE_LAZY_OFF) {
			dtrace_lazy_dofs_process(child);
		}
		lck_rw_unlock_shared(&dtrace_dof_mode_lock);

		return DTRACE_LAZY_DOFS_DUPLICATED;
	}
	lck_rw_unlock_shared(&dtrace_dof_mode_lock);

	return 0;
}