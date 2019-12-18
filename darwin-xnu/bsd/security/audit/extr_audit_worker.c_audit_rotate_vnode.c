#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
typedef  int /*<<< orphan*/ * kauth_cred_t ;
struct TYPE_4__ {int /*<<< orphan*/ * vc_ucred; } ;
struct TYPE_3__ {scalar_t__ aq_hiwater; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_CLOSE_FLAGS ; 
 int /*<<< orphan*/  AUDIT_WORKER_SX_XLOCK () ; 
 int /*<<< orphan*/  AUDIT_WORKER_SX_XUNLOCK () ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ audit_ctx ; 
 int /*<<< orphan*/  audit_drain_cv ; 
 int /*<<< orphan*/  audit_drain_kar ; 
 int /*<<< orphan*/  audit_enabled ; 
 scalar_t__ audit_file_rotate_wait ; 
 int /*<<< orphan*/  audit_mtx ; 
 int /*<<< orphan*/  audit_q ; 
 int audit_q_draining ; 
 scalar_t__ audit_q_len ; 
 TYPE_1__ audit_qctrl ; 
 struct vnode* audit_vp ; 
 int /*<<< orphan*/  audit_watermark_cv ; 
 int /*<<< orphan*/  audit_worker_cv ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  k_q ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 
 int /*<<< orphan*/  vn_close (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_get (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 

void
audit_rotate_vnode(kauth_cred_t cred, struct vnode *vp)
{
	kauth_cred_t old_audit_cred;
	struct vnode *old_audit_vp;

	KASSERT((cred != NULL && vp != NULL) || (cred == NULL && vp == NULL),
	    ("audit_rotate_vnode: cred %p vp %p", cred, vp));


	mtx_lock(&audit_mtx);
	if (audit_enabled && (NULL == vp)) {
		/* Auditing is currently enabled but will be disabled. */

		/*
		 * Disable auditing now so nothing more is added while the
		 * audit worker thread is draining the audit record queue.
		 */
		audit_enabled = 0;

		/*
		 * Drain the auditing queue by inserting a drain record at the
		 * end of the queue and waiting for the audit worker thread
		 * to find this record and signal that it is done before
		 * we close the audit trail.
		 */
		audit_q_draining = 1;
		while (audit_q_len >= audit_qctrl.aq_hiwater)
			cv_wait(&audit_watermark_cv, &audit_mtx);
		TAILQ_INSERT_TAIL(&audit_q, &audit_drain_kar, k_q);
		audit_q_len++;
		cv_signal(&audit_worker_cv);
	}

	/* If the audit queue is draining then wait here until it's done. */
	while (audit_q_draining)
		cv_wait(&audit_drain_cv, &audit_mtx);
	mtx_unlock(&audit_mtx);


	/*
	 * Rotate the vnode/cred, and clear the rotate flag so that we will
	 * send a rotate trigger if the new file fills.
	 */
	AUDIT_WORKER_SX_XLOCK();
	old_audit_cred = audit_ctx.vc_ucred;
	old_audit_vp = audit_vp;
	audit_ctx.vc_ucred = cred;
	audit_vp = vp;
	audit_file_rotate_wait = 0;
	audit_enabled = (audit_vp != NULL);
	AUDIT_WORKER_SX_XUNLOCK();

	/*
	 * If there was an old vnode/credential, close and free.
	 */
	if (old_audit_vp != NULL) {
		if (vnode_get(old_audit_vp) == 0) {
			vn_close(old_audit_vp, AUDIT_CLOSE_FLAGS,
			    vfs_context_kernel());
			vnode_put(old_audit_vp);
		} else
			printf("audit_rotate_vnode: Couldn't close "
			    "audit file.\n");
		kauth_cred_unref(&old_audit_cred);
	}
}