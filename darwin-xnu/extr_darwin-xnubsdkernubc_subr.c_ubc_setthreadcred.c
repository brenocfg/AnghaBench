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
typedef  int /*<<< orphan*/  thread_t ;
struct vnode {struct ubc_info* v_ubcinfo; } ;
struct uthread {int uu_flag; int /*<<< orphan*/  uu_ucred; } ;
struct ubc_info {int /*<<< orphan*/  ui_ucred; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UBCINFOEXISTS (struct vnode*) ; 
 int UT_SETUID ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_lock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

int
ubc_setthreadcred(struct vnode *vp, proc_t p, thread_t thread)
{
	struct ubc_info *uip;
	kauth_cred_t credp;
	struct uthread  *uthread = get_bsdthread_info(thread);

	if (!UBCINFOEXISTS(vp))
		return (1); 

	vnode_lock(vp);

	uip = vp->v_ubcinfo;
	credp = uip->ui_ucred;

	if (!IS_VALID_CRED(credp)) {
		/* use per-thread cred, if assumed identity, else proc cred */
		if (uthread == NULL || (uthread->uu_flag & UT_SETUID) == 0) {
			uip->ui_ucred = kauth_cred_proc_ref(p);
		} else {
			uip->ui_ucred = uthread->uu_ucred;
			kauth_cred_ref(uip->ui_ucred);
		}
	} 
	vnode_unlock(vp);

	return (0);
}