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
struct vnode {int /*<<< orphan*/  v_label; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int ACCESS_MODE_TO_VNODE_MASK (int) ; 
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mac_cred_check_enforce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_vnode_enforce ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_check_access ; 

int
mac_vnode_check_access(vfs_context_t ctx, struct vnode *vp,
    int acc_mode)
{
	kauth_cred_t cred;
	int error;
	int mask;

#if SECURITY_MAC_CHECK_ENFORCE
	/* 21167099 - only check if we allow write */
	if (!mac_vnode_enforce)
		return 0;
#endif
	cred = vfs_context_ucred(ctx);
	if (!mac_cred_check_enforce(cred))
		return (0);
	/* Convert {R,W,X}_OK values to V{READ,WRITE,EXEC} for entry points */
	mask = ACCESS_MODE_TO_VNODE_MASK(acc_mode);
	MAC_CHECK(vnode_check_access, cred, vp, vp->v_label, mask);
	return (error);
 }