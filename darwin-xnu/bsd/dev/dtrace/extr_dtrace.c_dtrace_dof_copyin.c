#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  hdr ;
struct TYPE_7__ {int dofh_loadsz; } ;
typedef  TYPE_1__ dof_hdr_t ;

/* Variables and functions */
 int E2BIG ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 scalar_t__ copyin (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  dtrace_dof_error (TYPE_1__*,char*) ; 
 scalar_t__ dtrace_dof_maxsize ; 
 int /*<<< orphan*/  dtrace_lock ; 
 TYPE_1__* kmem_alloc_aligned (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free_aligned (TYPE_1__*,int) ; 

__attribute__((used)) static dof_hdr_t *
dtrace_dof_copyin(user_addr_t uarg, int *errp)
{
	dof_hdr_t hdr, *dof;

	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_NOTOWNED);

	/*
	 * First, we're going to copyin() the sizeof (dof_hdr_t).
	 */
	if (copyin(uarg, &hdr, sizeof (hdr)) != 0) {
		dtrace_dof_error(NULL, "failed to copyin DOF header");
		*errp = EFAULT;
		return (NULL);
	}

	/*
	 * Now we'll allocate the entire DOF and copy it in -- provided
	 * that the length isn't outrageous.
	 */
	if (hdr.dofh_loadsz >= (uint64_t)dtrace_dof_maxsize) {
		dtrace_dof_error(&hdr, "load size exceeds maximum");
		*errp = E2BIG;
		return (NULL);
	}

	if (hdr.dofh_loadsz < sizeof (hdr)) {
		dtrace_dof_error(&hdr, "invalid load size");
		*errp = EINVAL;
		return (NULL);
	}

	dof = kmem_alloc_aligned(hdr.dofh_loadsz, 8, KM_SLEEP);

        if (copyin(uarg, dof, hdr.dofh_loadsz) != 0  ||
	  dof->dofh_loadsz != hdr.dofh_loadsz) {
	    kmem_free_aligned(dof, hdr.dofh_loadsz);
	    *errp = EFAULT;
	    return (NULL);
	}	    

	return (dof);
}