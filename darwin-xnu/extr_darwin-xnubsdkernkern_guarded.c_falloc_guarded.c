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
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int u_int ;
struct proc {int dummy; } ;
struct gfp_crarg {scalar_t__ gca_guard; int gca_attrs; } ;
struct fileproc {int dummy; } ;
typedef  scalar_t__ guardid_t ;
typedef  int /*<<< orphan*/  crarg ;

/* Variables and functions */
 int EINVAL ; 
 int GUARD_ALL ; 
 int GUARD_REQUIRED ; 
 int /*<<< orphan*/  bzero (struct gfp_crarg*,int) ; 
 int falloc_withalloc (struct proc*,struct fileproc**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfp_crarg*) ; 
 int /*<<< orphan*/  guarded_fileproc_alloc_init ; 

int
falloc_guarded(struct proc *p, struct fileproc **fp, int *fd,
    vfs_context_t ctx, const guardid_t *guard, u_int attrs)
{
	struct gfp_crarg crarg;

	if (((attrs & GUARD_REQUIRED) != GUARD_REQUIRED) ||
	    ((attrs & ~GUARD_ALL) != 0) || (*guard == 0))
		return (EINVAL);

	bzero(&crarg, sizeof (crarg));
	crarg.gca_guard = *guard;
	crarg.gca_attrs = attrs;

	return (falloc_withalloc(p, fp, fd, ctx, guarded_fileproc_alloc_init,
	    &crarg));
}