#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  scalar_t__ vfs_context_t ;
typedef  int /*<<< orphan*/  kauth_action_t ;
struct TYPE_4__ {scalar_t__ v_type; } ;

/* Variables and functions */
 int EACCES ; 
 int EPERM ; 
 scalar_t__ VBAD ; 
 int kauth_authorize_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ; 
 int /*<<< orphan*/  vfs_context_ucred (scalar_t__) ; 
 int /*<<< orphan*/  vnode_scope ; 

int
vnode_authorize(vnode_t vp, vnode_t dvp, kauth_action_t action, vfs_context_t ctx)
{
	int	error, result;

	/*
	 * We can't authorize against a dead vnode; allow all operations through so that
	 * the correct error can be returned.
	 */
	if (vp->v_type == VBAD)
		return(0);
	
	error = 0;
	result = kauth_authorize_action(vnode_scope, vfs_context_ucred(ctx), action,
		   (uintptr_t)ctx, (uintptr_t)vp, (uintptr_t)dvp, (uintptr_t)&error);
	if (result == EPERM)		/* traditional behaviour */
		result = EACCES;
	/* did the lower layers give a better error return? */
	if ((result != 0) && (error != 0))
	        return(error);
	return(result);
}