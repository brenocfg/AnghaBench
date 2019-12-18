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
struct guarded_kqueue_np_args {int guardflags; int /*<<< orphan*/  guard; } ;
struct gfp_crarg {int gca_attrs; scalar_t__ gca_guard; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int GUARD_ALL ; 
 int GUARD_REQUIRED ; 
 int copyin (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  guarded_fileproc_alloc_init ; 
 int kqueue_body (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfp_crarg*,int /*<<< orphan*/ *) ; 

int
guarded_kqueue_np(proc_t p, struct guarded_kqueue_np_args *uap, int32_t *retval)
{
	if (((uap->guardflags & GUARD_REQUIRED) != GUARD_REQUIRED) ||
	    ((uap->guardflags & ~GUARD_ALL) != 0))
		return (EINVAL);

	int error;
	struct gfp_crarg crarg = {
		.gca_attrs = uap->guardflags
	};

	if ((error = copyin(uap->guard,
	    &(crarg.gca_guard), sizeof (crarg.gca_guard))) != 0)
		return (error);

	if (crarg.gca_guard == 0)
		return (EINVAL);

	return (kqueue_body(p, guarded_fileproc_alloc_init, &crarg, retval));
}