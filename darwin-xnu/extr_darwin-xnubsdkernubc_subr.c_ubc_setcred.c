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
struct vnode {struct ubc_info* v_ubcinfo; } ;
struct ubc_info {int /*<<< orphan*/  ui_ucred; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UBCINFOEXISTS (struct vnode*) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_lock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

int
ubc_setcred(struct vnode *vp, proc_t p)
{
	struct ubc_info *uip;
	kauth_cred_t credp;

	/* If there is no ubc_info, deny the operation */
	if ( !UBCINFOEXISTS(vp))
		return (0); 

	/*
	 * Check to see if there is already a credential reference in the
	 * ubc_info; if there is not, take one on the supplied credential.
	 */
	vnode_lock(vp);
	uip = vp->v_ubcinfo;
	credp = uip->ui_ucred;
	if (!IS_VALID_CRED(credp)) {
		uip->ui_ucred = kauth_cred_proc_ref(p);
	} 
	vnode_unlock(vp);

	return (1);
}